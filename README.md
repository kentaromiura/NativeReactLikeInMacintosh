Macintosh fake-react native
===

This is a porting of my afternoon experiment to the Macintosh platform

It's based on the work I've done for Windows 3.11 for [this twitter thread](https://twitter.com/kentaromiura/status/1216742960408055809)


Requirements:
===
You need a build of https://github.com/autc04/Retro68, that includes the Apple Universal Interfaces,
to get those download the image from one of the links, open it in Basilisk and then copy those file back to windows: I used HVFExplorer and I copied them w/out the resource partition, seems to work.
About basilisk, I'm using the windows build, in order to enable the sharing between windows and basilisk I had to add `ignoresegv true` to the preference file as it keeps crashing otherwise in Windows 10.

To simplify this step you can find a pce/macplus image [linked in this article](http://www.toughdev.com/content/2018/12/developing-68k-mac-apps-with-codelite-ide-retro68-and-pce-macplus-emulator/)
I personally did not try it but should work fine, but probably you'll need to pull the latest changes from git (recursively).

I used WSL2, you can get this to work fine with WSL1 probably as long as you use a windows shared folder mounted on your linux for using the `launchAPPL` utility, otherwise you'll have to use HVFExplorer to copy the executable to the mac image.
If you use the launchAPPL I suggest to make an alias like
```
alias launchAPPL='/path/to/Retro68/build/build-host/LaunchAPPL/Client/LaunchAPPL -e shared --shared-directory /mnt/c/share'
```
If you use other emulators such as minivmac2 you can probably use the network share, it doesn't work on Basilisk though.

Ensure the node dependencies are installed by running yarn.
I wrote a script to create and embed the sources as mac resources inside the executable resource partition,
node wasn't strictly necessary for this, but I still needed babel to convert the JSX to ES3 that can be run in duktape, so that's why it's a nodejs file.

In the Makefile you'll need to edit the path to your Retro68 build, just change the value of `CMAKE_TOOLCHAIN_FILE` to the appropriate path.

How does this work?
===

The `main.c` is just a simple barebone program that initialize everything needed by the mac to start up an application, then it loads [duktape](https://duktape.org/) a real stack based JS engine that can run the code that babel outputs; the dukbridge file creates 2 duktape native functions that will we use to bridge the JS world to the native world.

First though we load the _app/fakeReact.js_ that creates some globals that we need, `React` with its 2 functions `createElement` and `mount`, plus a `MessageBox` and a `Dialog` _native_ components (you might notice that will call some weird `React.duktape.` methods, explained later), and two implementation specific things, an empty object property named `duktape`, under the `React` global to avoid too much pollution, and a `native` property that simply maps all the native components, this is used by `React.mount` to know if it needs to call the _native_ function or continue rendering; a little note here is that I didn't implement a fully descendant reconciler, it only supports 2 levels, the one needed for the demo, sorry!

Anyway, at this point the `populateCtx` in _dukbridge.c_ runs and connects the JS world to the native world by adding the `showDialog` and `showMessageBox` native functions to `React.duktape`.

At this point the main setup is done, so the _app/index.js_ is loaded first and the `main` function is mounted.
