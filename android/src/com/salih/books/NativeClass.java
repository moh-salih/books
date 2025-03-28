package com.salih.books;


import android.Manifest;
import android.app.Activity;
import android.content.ContentResolver;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Environment;
import android.provider.MediaStore;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import java.util.ArrayList;
import android.Manifest;
import android.content.ContentResolver;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.TextView;
import java.util.ArrayList;
import java.util.List;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.provider.Settings;
import android.util.Log;
import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import static java.lang.System.out;

public class NativeClass {
    private static final int STORAGE_PERMISSION_CODE = 100;
    private static final int STORAGE_PERMISSION_REQUEST_CODE = 100;
    private static final String TAG = "JavaSalih";


    public static void requestStoragePermission(Activity activity) {
        if (activity == null) {
            return;
        }

        // For Android 11 (API 30) and above
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.R) {
            try {
                // Request MANAGE_EXTERNAL_STORAGE for full file access
                android.content.Intent intent = new android.content.Intent(
                    android.provider.Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION);
                android.net.Uri uri = android.net.Uri.fromParts("package", activity.getPackageName(), null);
                intent.setData(uri);
                activity.startActivityForResult(intent, STORAGE_PERMISSION_CODE);
            } catch (Exception e) {
                // Fallback if the above fails
                android.content.Intent intent = new android.content.Intent(
                    android.provider.Settings.ACTION_MANAGE_ALL_FILES_ACCESS_PERMISSION);
                activity.startActivityForResult(intent, STORAGE_PERMISSION_CODE);
            }
        }
        // For Android 10 and below
        else {
            if (ContextCompat.checkSelfPermission(activity, Manifest.permission.READ_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED ||
                ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                    != PackageManager.PERMISSION_GRANTED) {

                ActivityCompat.requestPermissions(activity,
                    new String[]{
                        Manifest.permission.READ_EXTERNAL_STORAGE,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE
                    },
                    STORAGE_PERMISSION_CODE);
            }
        }
    }

    public static boolean isStoragePermissionGranted(Activity activity) {
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.R) {
            return android.os.Environment.isExternalStorageManager();
        } else {
            return ContextCompat.checkSelfPermission(activity, Manifest.permission.READ_EXTERNAL_STORAGE)
                == PackageManager.PERMISSION_GRANTED &&
                ContextCompat.checkSelfPermission(activity, Manifest.permission.WRITE_EXTERNAL_STORAGE)
                == PackageManager.PERMISSION_GRANTED;
        }
    }

    public static String[] getAllPdfs(Activity activity) {
        List<String> pdfFiles = new ArrayList<>();

        if (activity == null) {
            Log.e(TAG, "Activity is null!");
            return new String[0]; // Return empty array
        }

        Uri collection = MediaStore.Files.getContentUri("external");

        String[] projection = {
            MediaStore.Files.FileColumns.DISPLAY_NAME,
            MediaStore.Files.FileColumns.RELATIVE_PATH,
            MediaStore.Files.FileColumns.DATA
        };

        String selection = MediaStore.Files.FileColumns.MIME_TYPE + "=?";
        String[] selectionArgs = new String[]{"application/pdf"};
        String sortOrder = MediaStore.Files.FileColumns.DATE_ADDED + " DESC";

        ContentResolver contentResolver = activity.getContentResolver();
        try (Cursor cursor = contentResolver.query(collection, projection, selection, selectionArgs, sortOrder)) {
            if (cursor != null) {
                while (cursor.moveToNext()) {
                    String displayName = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Files.FileColumns.DISPLAY_NAME));
                    String relativePath = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Files.FileColumns.RELATIVE_PATH));

                    System.out.println("Android saying: " + Environment.getExternalStorageDirectory().getAbsolutePath());
                    String absolutePath = Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + relativePath + "/" + displayName;
                    pdfFiles.add(absolutePath);
                }
            }
        } catch (Exception e) {
            Log.e(TAG, "Error querying PDFs", e);
        }

        return pdfFiles.toArray(new String[0]); // Convert list to array
    }


}
