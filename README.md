# sysrepo-plugins-common
Set of utilities/functionalities which can be used for easier build of sysrepo plugins.

# Build
Use the following set of commands to build the project:
```sh
git clone https://github.com/mcindrich/sysrepo-plugins-common.git
cd sysrepo-plugins-common
mkdir build; cd build
cmake .. # setup CMAKE_INSTALL_PREFIX if needed
make -j
```

# Documentation
As for the documentation, the files are documented using doxygen comments:
```sh
mkdir docs
doxygen Doxyfile
```
Use doxygen or browse ```.h``` files for an API description.