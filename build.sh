#!/bin/bash
#
#
#    CEsvga2 - ChrisEric1 Super Video Graphics Array 2
#    Copyright (C) 2023-2025, Christopher Eric Lentocha
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License as published
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.
#
#    You should have received a copy of the GNU Affero General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
#
clear
set -x
rm -rfv "./keout"
rm -rfv "./build"
rm -rfv "./resolutionSet/build"
set -e
python3 -m pip install -r "./requirements.txt"
xcodebuild build -configuration i386
xcodebuild build -configuration x86_64
python3 "./fix-macho32.py" "./build/i386/CEsvga2.kext/Contents/MacOS/CEsvga2"
mkdir -pv "./keout/"
cp -rfv "./build/i386" "./keout/universal"
rm -rfv "./keout/universal/CEsvga2.kext/Contents/MacOS/CEsvga2"
lipo -create -output "./keout/universal/CEsvga2.kext/Contents/MacOS/CEsvga2" "./build/i386/CEsvga2.kext/Contents/MacOS/CEsvga2" "./build/x86_64/CEsvga2.kext/Contents/MacOS/CEsvga2"
python3 "./fix-macho32.py" "./keout/universal/CEsvga2.kext/Contents/MacOS/CEsvga2"
rm -rfv "./build/i386/CEsvga2.kext/Contents/_CodeSignature"
rm -rfv "./build/x86_64/CEsvga2.kext/Contents/_CodeSignature"
rm -rfv "./keout/universal/CEsvga2.kext/Contents/_CodeSignature"
cp -rfv "./Info-i386.plist" "./build/i386/CEsvga2.kext/Contents/Info.plist"
cp -rfv "./Info-x86_64.plist" "./build/x86_64/CEsvga2.kext/Contents/Info.plist"
cp -rfv "./Info-universal.plist" "./keout/universal/CEsvga2.kext/Contents/Info.plist"
cp -rfv "./build/i386" "./keout/"
cp -rfv "./build/x86_64" "./keout/"
cd "./resolutionSet"
xcodebuild build -configuration i386
xcodebuild build -configuration x86_64
cd "./../"
python3 "./fix-macho32.py" "./resolutionSet/build/i386/resolutionSet"
cp -rfv "./resolutionSet/build/i386/resolutionSet" "./keout/i386/resolutionSet"
cp -rfv "./resolutionSet/build/x86_64/resolutionSet" "./keout/x86_64/resolutionSet"
lipo -create -output "./keout/universal/resolutionSet" "./keout/i386/resolutionSet" "./keout/x86_64/resolutionSet"
python3 "./fix-macho32.py" "./keout/universal/resolutionSet"
