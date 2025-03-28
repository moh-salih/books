cmake_minimum_required(VERSION 3.16)

project(books VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)



find_package(Qt6 REQUIRED COMPONENTS Quick Gui Core Sql Pdf)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appbooks
    main.cpp
)

qt_add_qml_module(appbooks
    URI books
    VERSION 1.0
    QML_FILES
        Main.qml
        RESOURCES android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml android/res/xml/qtprovider_paths.xml android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/gradle.properties android/gradlew android/gradlew.bat
        RESOURCES android/src/com/salih/books/NativeClass.java
        SOURCES core/database/databasemanager.h core/database/databasemanager.cpp
        SOURCES core/data/book.h core/data/book.cpp
        SOURCES core/data/author.h core/data/author.cpp


        QML_FILES frontend/screens/PdfScreen/PdfScreen.qml
        QML_FILES frontend/screens/PdfScreen/PdfViewer.qml
        RESOURCES pdfs/pride-and-prejudice-jane-austen.pdf
        SOURCES core/models/booklistmodel.h core/models/booklistmodel.cpp
        QML_FILES frontend/screens/BookListScreen/BookListScreen.qml
        QML_FILES frontend/screens/BookListScreen/BookItem.qml
        RESOURCES images/books_icon2.png
        RESOURCES fonts/comic-khazi-font/ComicKhazi-X05j.ttf
        QML_FILES frontend/screens/BookListScreen/AllBooks.qml
        QML_FILES frontend/screens/BookListScreen/FavoriteBooks.qml
        RESOURCES images/update_icon_1.png
        RESOURCES images/delete_icon_1.png
        RESOURCES images/permission_icon_1.png
        QML_FILES
        QML_FILES frontend/screens/BookListScreen/BookListItem.qml
        SOURCES core/repository/interfaces/iFavoriteBookRepository.h core/repository/interfaces/iAuthorrepository.h core/repository/interfaces/iTableRepository.h core/repository/interfaces/iBookrepository.h
        SOURCES core/repository/bookrepository.h core/repository/favoritebookrepository.cpp core/repository/favoritebookrepository.h core/repository/bookrepository.cpp core/repository/authorrepository.h core/repository/authorrepository.cpp
        RESOURCES icons/fontello-07c00b8d/font/fontello.ttf
        SOURCES core/models/favoritebooklistmodel.h core/models/favoritebooklistmodel.cpp
        SOURCES core/models/basebooklistmodel.h core/models/basebooklistmodel.cpp
        QML_FILES frontend/screens/WelcomeScreen/WelcomeScreen.qml
        RESOURCES images/heart_icon.png
        RESOURCES images/unheart_icon.png
        QML_FILES frontend/screens/BookListScreen/BookCategories.qml
        QML_FILES
        RESOURCES images/white_full_me.png images/trans_full_me.png
        RESOURCES fonts/Boldonse/Boldonse-Regular.ttf
        SOURCES core/repository/categoryrepository.h core/repository/categoryrepository.cpp
        SOURCES core/repository/interfaces/ICategoryRepository.h
        SOURCES core/data/category.h
        SOURCES core/models/categorylistmodel.h core/models/categorylistmodel.cpp
        QML_FILES frontend/screens/BookListScreen/CategoryBooks.qml
        QML_FILES frontend/screens/BookListScreen/BookList.qml
        SOURCES core/repository/interfaces/IBookCategoryRepository.h
        SOURCES core/repository/bookcategoryrepository.h core/repository/bookcategoryrepository.cpp

)



if(ANDROID)
    set_property(TARGET appbooks APPEND PROPERTY
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
    )

    # Add openssl support
    include("$ENV{ANDROID_HOME}/android_openssl/android_openssl.cmake")
    add_android_openssl_libraries(appbooks)


endif()
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appbooks PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appbooks
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appbooks
    PRIVATE Qt6::Quick Qt6::Gui Qt6::Core Qt6::Sql Qt6::Pdf
)

include(GNUInstallDirs)
install(TARGETS appbooks
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
