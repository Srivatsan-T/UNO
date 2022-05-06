# CS1023-SDF-Project-Team-16 "You Know UNO?"
CS1023-SDF-Project-Team-16 created by GitHub Classroom

## Building

1. Download Qt creator and clone the main branch of the repository.
2. Once the project is imported, go to Projects Tab and switch to change the RUN configurations.
3. Scroll down to Build Environment under Environment section and append the SDL library/bin directory included in the repo to the PATH.
2. Build the project using Qt 6.1.2 MinGW 64-bit compiler and CMake.
3. Find the generated executable from the build folder and make sure the dll's and sounds1 folder is present. If not add them from the libraries/bin folder.
4. Run the executable and enjoy playing!

## Testing
1. Download Qt creator and clone the main branch of the repository.
2. Now try and run the cmake file from the UNO-TEST folder of the repository.
3. Run the executable and you can view the result of all the tests as output.
4. Feel free to add most tests by adding your test as a function in the private slots: tag.
5. For more details on testing check out the official Qt Documentation for the same. https://doc.qt.io/qt-5/qtest-overview.html

## Licenses
1. The projects uses Qt6 framework and SDL libraries. Note that we use Qt's open source licensing and have thereby made our project licensed under GPL3.0 and we hereby also explicitly acknowledge the usage of Qt6 and Qt creator. 
3. SDL library is available under zlib license and is also free to use. We have included the SDL license under the libraries folder.
4. We also have a bunch of .mp3 files to be used as in-game music and sound effects. All of the files are free to use and we have also included the source website and each website's licensing in the sounds1 folder as a proof that they are indeed free for use.

## License Websites
1.  Visit https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5 to check Qt's documentation on using open       source license. 
2.  Visit https://www.libsdl.org/license.php for SDL's zlib license.
3.  Visit https://mixkit.co/license/#sfxFree for MixKit license.
4.  Visit https://www.soundjay.com/tos.html for the offical sound-jay license.
5.  Visit https://www.ashamaluevmusic.com/terms for the actual ashamaluevmusic license documentation.

## Documentation
1.  We used doxygen for code documentatiion and usage guide.
2.  We used formatted comments in our code as well as the inbuilt documentor in doxygen to get the manual.
3.  You can find it here : https://github.com/IITH-CS1023/cs1023-sdf-project-team-16/blob/main/Documentation%20of%20Code.pdf

## Releases

If building projects isn't your thing you can download the latest release and extract it to find the game ready to play!
Look up here for all the releases https://github.com/IITH-CS1023/cs1023-sdf-project-team-16/releases
