#!/bin/bash

# Define variables
APP_NAME="TextEditor"
BUNDLE_NAME="${APP_NAME}.app"
EXECUTABLE_NAME="texteditor"  # Replace with the name of your built executable
BUILD_DIR="cmake-build-debug"
ICON_FILE="your_icon.icns"  # Replace with your icon file if you have one

# Build the application
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake ..
make
cd ..

# Create the directory structure for the app bundle
mkdir -p "${BUNDLE_NAME}/Contents/MacOS"
mkdir -p "${BUNDLE_NAME}/Contents/Resources"

# Copy the executable
cp "${BUILD_DIR}/${EXECUTABLE_NAME}" "${BUNDLE_NAME}/Contents/MacOS/"

# Create the Info.plist file
cat > "${BUNDLE_NAME}/Contents/Info.plist" <<EOL
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>${EXECUTABLE_NAME}</string>
    <key>CFBundleIdentifier</key>
    <string>com.yourcompany.${APP_NAME}</string>
    <key>CFBundleName</key>
    <string>${APP_NAME}</string>
    <key>CFBundleIconFile</key>
    <string>${ICON_FILE}</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleSignature</key>
    <string>????</string>
    <key>CFBundleVersion</key>
    <string>1.0</string>
</dict>
</plist>
EOL

# Copy the icon file if it exists
if [ -f "${ICON_FILE}" ]; then
    cp "${ICON_FILE}" "${BUNDLE_NAME}/Contents/Resources/"
fi

# Make the executable file executable
chmod +x "${BUNDLE_NAME}/Contents/MacOS/${EXECUTABLE_NAME}"

echo "Application bundle ${BUNDLE_NAME} created successfully."
