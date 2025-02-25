#!/bin/bash

# set -x

# https://scriptingosx.com/2021/07/notarize-a-command-line-tool-with-notarytool/

VERSION=$1

if [[ -z "${VERSION}" ]]; then
  echo "no version specified."
  echo "invoke with 'notarize-macos.sh <version> <cert_id> <keychain_profile>'"
  exit
fi

# the value for CERT_ID is the team name of the "Application ID"
# certificate obtained in the Apple developer portal, then imported
# into the system's keychain.
CERT_ID=$2

if [[ -z "${CERT_ID}" ]]; then
  echo "no cert_id specified."
  echo "invoke with 'notarize-macos.sh <version> <cert_id> <keychain_profile>'"
  exit
fi

# the keychain profile is created locally as follows:
#   xcrun notarytool store-credentials --apple-id "name@example.com"
# during the creation process you will be prompted for an app-level
# password; this was generated in the apple developer portal and
# saved in your password store. we usually call this keychain
# "musikcube-notarytool"
KEYCHAIN_PROFILE=$3

if [[ -z "${KEYCHAIN_PROFILE}" ]]; then
  echo "no keychain_profile specified."
  echo "invoke with 'notarize-macos.sh <version> <cert_id> <keychain_profile>'"
  exit
fi

ARCH=$(uname -m)
DIR="./dist/${VERSION}/musikcube_standalone_macos_${ARCH}_${VERSION}"
ARCHIVE="./dist/${VERSION}/musikcube_standalone_macos_${ARCH}_${VERSION}.zip"

pushd $DIR
codesign --remove-signature musikcube musikcubed libmusikcore.dylib
codesign --remove-signature lib/*.dylib
codesign --remove-signature plugins/*.dylib

codesign --force --timestamp --options=runtime --sign $CERT_ID musikcube musikcubed
codesign --force --timestamp --sign $CERT_ID libmusikcore.dylib
codesign --force --timestamp --sign $CERT_ID lib/*.dylib
codesign --force --timestamp --sign $CERT_ID plugins/*.dylib
popd

ditto -c -k --keepParent $DIR $ARCHIVE

xcrun notarytool submit $ARCHIVE --keychain-profile "$KEYCHAIN_PROFILE" --wait
