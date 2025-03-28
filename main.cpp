#include <QtGui>
#include <QtCore>
#include <QtQuick>

#include "core/database/databasemanager.h"
#include "core/repository/bookrepository.h"
#include "core/repository/authorrepository.h"
#include "core/repository/favoritebookrepository.h"
#include "core/repository/categoryrepository.h"
#include "core/repository/bookcategoryrepository.h"

#include "core/models/booklistmodel.h"
#include "core/models/favoritebooklistmodel.h"
#include "core/models/categorylistmodel.h"

#ifdef Q_OS_ANDROID
class AndroidHelper: public QObject{
    Q_OBJECT
public:

    explicit AndroidHelper(QObject * parent = nullptr): QObject(parent){
        activity = QJniObject::callStaticObjectMethod(
            "org/qtproject/qt/android/QtNative",
            "activity",
            "()Landroid/app/Activity;"
            );
    }

    Q_INVOKABLE void requestStoragePermission() {
        if (!activity.isValid()) return;

        QJniObject::callStaticMethod<void>(
            "com/salih/books/NativeClass",
            "requestStoragePermission",
            "(Landroid/app/Activity;)V",
            activity.object<jobject>()
            );
    }

    Q_INVOKABLE bool isStoragePermissionGranted() {
        if (!activity.isValid()) return false;

        return QJniObject::callStaticMethod<jboolean>(
            "com/salih/books/NativeClass",
            "isStoragePermissionGranted",
            "(Landroid/app/Activity;)Z",
            activity.object<jobject>()
            );
    }



    Q_INVOKABLE QList<QString> getAllPdfs() {
        if (!activity.isValid()) return{};

        if (!activity.isValid()) {
            qWarning() << "Invalid Android activity!";
            return {};
        }

        QJniObject pdfArray = QJniObject::callStaticObjectMethod(
            "com/salih/books/NativeClass",
            "getAllPdfs",
            "(Landroid/app/Activity;)[Ljava/lang/String;", // Corrected JNI signature
            activity.object<jobject>()
            );

        QList<QString> pdfList;
        if (!pdfArray.isValid()) return pdfList;

        QJniEnvironment env;
        jobjectArray javaArray = static_cast<jobjectArray>(pdfArray.object<jobjectArray>());
        jsize length = env->GetArrayLength(javaArray);

        for (jsize i = 0; i < length; i++) {
            QJniObject pdfPath(env->GetObjectArrayElement(javaArray, i));
            pdfList.append(pdfPath.toString());

            // env->DeleteLocalRef(pdfPath.object<jobject>());
        }

        return pdfList;
    }

private:
    QJniObject activity;
};

#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;

    DatabaseManager databaseManager(&app);

    // Initialize tables
    auto bookRepository = databaseManager.createRepository<BookRepository>();
    auto authorRepository = databaseManager.createRepository<AuthorRepository>();
    auto favoriteBookRepository = databaseManager.createRepository<FavoriteBookRepository>();
    auto categoryRepository = databaseManager.createRepository<CategoryRepository>();
    auto bookCategoryRepository = databaseManager.createRepository<BookCategoryRepository>();


    if(authorRepository->getAllAuthors().count() == 0){
        authorRepository->addAuthor({0, "Unknown", QDateTime::currentDateTime(), QDateTime::currentDateTime(), "images/default_author.png"});
    }

    // View models
    BookListModel * bookListModel = new BookListModel(bookRepository, favoriteBookRepository, &app);
    FavoriteBookListModel * favoriteBookListModel = new FavoriteBookListModel(favoriteBookRepository, &app);
    CategoryListModel * categoryListModel = new CategoryListModel(categoryRepository, &app);

    engine.rootContext()->setContextProperty("databaseManager", &databaseManager);
    engine.rootContext()->setContextProperty("bookRepository", bookRepository);
    engine.rootContext()->setContextProperty("authorRepository", authorRepository);

    engine.rootContext()->setContextProperty("bookListModel", bookListModel);

    engine.rootContext()->setContextProperty("favoriteBookListModel", favoriteBookListModel);
    engine.rootContext()->setContextProperty("categoryListModel", categoryListModel);




#ifdef Q_OS_ANDROID
    AndroidHelper androidHelper(&app);
    engine.rootContext()->setContextProperty("androidHelper", &androidHelper);
#endif

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("books", "Main");

    return app.exec();
}


#include "main.moc"
