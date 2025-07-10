- [X] Add CMake for build
  - [X] Continue improving CMake build
  - [ ] Think what to do with Makefile
- [ ] Dynamic Logging (for now just hardcoded printf's)
  - [ ] Option to disable completely during compilation
  - [ ] APIs to change log level at runtime
  - [ ] APIs to redirect logging to FD
- [ ] Set test build to OFF by default on project release
- [ ] Think if throwing ERR is a good idea, or switch to Exception class that wraps this value
- [ ] All GIO/GLIBMM calls are throwing Gio::Error exceptions. Need to map them to our exception
- [ ] At first make everything on callback. Like how to obtain available adapters at init - set adapter callback and call init function - the init will obtain adapters and pass to callback
- [ ] Make a fully C++ library
  - [ ] Use objects, std::variant etc in callbacks
  - [ ] Throw exceptions in APIs
- [ ] Adapter parsing problem:
  - [ ] When asking BlueZ for objects, the Adapter's path will be /org/bluez/hci0, however any associated devices will be smth like "/org/bluez/hci0/dev_AC_C0_48_FF_E7_7C". So, how should we determince, that we are working with controller right now?
  Possible solution:
	Adapters have "org.bluez.Adapter1" interface, but associated devices "org.bluez.Device1". We can try to find if X object has what interface and based on that associate all other properties
- [ ] Re-evaluate the context alloc/destroy. It doesn't seems right that parallel thread can have a valid ref while libctx was destroyed