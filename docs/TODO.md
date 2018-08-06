## TODO LIST
### Build and Distribution
- [ ] Create configure script
  - [ ] Download dependencies (Qt and Boost)
  - [ ] Compile using Qt as static or dynamic
  - [ ] Compile Boost as static
  - [ ] Compile application
  - [ ] Create Distributable tar file with version number
- [X] Release binaries in tar.gz archives for use without end user compilation
### Structure
- [ ] Separate configuration tool from daemon (eliminate Qt dependency from daemon)
  - [ ] Use non qt timer loop (https://www.boost.org/doc/libs/1_67_0/doc/html/boost_asio/tutorial/tuttimer3/src.html)
- [ ] Create detailed documentation
  - [ ] Create build documentation
  - [ ] Create installation documentation
  - [ ] Create usage documentation
- [ ] Organize code and files for more modular use and less confusion
### Functionality
- [ ] Add ability to install engine on system (service file, configuration, app) within tool
- [ ] Add Compound scorechecker to check for multiple subissues in a single issue
- [ ] Create a way to make template scorecheckers
- [ ] Allow ability to have template scorecheckers which can create issues on the target machine
  - [ ] Allow template scorecheckers to contain bash scripts where variables can be replaced
  - [ ] Create window to customize/create template scorecheckers
- [ ] Allow manipulation of current issues in configuration
  - [X] Allow deletion of issues from current configuration
  - [ ] Allow rearranging issues
  - [ ] Allow copying/cutting and pasting issues
- [ ] Create mechanism for loading templates into the configuration tool
- [X] Allow export of configuration in both binary and xml format (more later hopefully: json, etc)
- [ ] Create file or mechanism with important variables like app version and text
  - [ ] Make the global variable for version
  - [ ] Make translation easier
- [ ] Integrate with other tools for generating an image (Ubuntu, Fedora, Arch, etc) using templates
- [ ] Setup notify-send popup for gain or loss of points
- [ ] Replace aplay with static library to remove dependency
### Aesthetics
- [ ] Change the name of ScoringEngine to something better...
- [ ] Add a splash screen to the GUI editor
