# Sterling's Nucle Minimal Viable Product Project
## Directory structure
- 'app' - developer-written code. Directories created for each module/function. Group sources and includes in the same directory.
    - 'hal' - abstraction between develop-written code and CubeMX constants (e.g. IO mappings)
    - 'rtos' - entry point into developer-written code from CubeMX project.
- 'cmake' - CubeMX generated files for building the project-generated code.
- 'Core' - CubeMX generated files for top-level project code.
- 'Drivers' - CubeMX generated files for HAL drivers.
- 'Middlewares' - CubeMX generated files for relevant libraries (e.g. FreeRTOS).
