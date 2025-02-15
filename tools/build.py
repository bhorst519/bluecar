import argparse, os, sys

repoRoot = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

#---------------------------------------------------------------------------------------------------
# Constants for build targets
#---------------------------------------------------------------------------------------------------
firmware_dirs = {
    "stersmith": os.path.join(repoRoot, "stersmithNucleoMvp"),
    "EIM": os.path.join(repoRoot, "EIM", "firmware"),
}

#---------------------------------------------------------------------------------------------------
# Constants
#---------------------------------------------------------------------------------------------------
class bcolors:
    OKRED = "\033[91m"
    OKBLUE = "\033[94m"
    OKCYAN = "\033[96m"
    OKGREEN = "\033[92m"
    OKMAGENTA = "\033[95m"
    ENDC = "\033[0m"

default_targets = [key for key in firmware_dirs]

def get_args():
    parser = argparse.ArgumentParser()

    parser.add_argument("-t", "--targets", dest="targets", nargs="+", default=default_targets, \
        help="Targets to build.")
    parser.add_argument("-b", "--build_config", dest="build_config", nargs="+", default=["Debug"], \
        help="Build configs to build for targets.")

    return parser.parse_args()

#---------------------------------------------------------------------------------------------------
# Run builds
#---------------------------------------------------------------------------------------------------
args = get_args()
build_summary = ""

for target in args.targets:
    for build in args.build_config:
        target_source_dir = firmware_dirs[target]
        target_build_dir = os.path.join(target_source_dir, "build", build)

        res = 0
        build_str = f"target: {target} - {build}"
        if res == 0:
            print(f"{bcolors.OKMAGENTA}Configuring build for {build_str}{bcolors.ENDC}")
            res = os.system(f"cmake -DCMAKE_BUILD_TYPE={build} -S {target_source_dir} -B {target_build_dir} -G Ninja")
        if res == 0:
            print(f"{bcolors.OKMAGENTA}Starting build for {build_str}{bcolors.ENDC}")
            os.system(f"cmake --build {target_build_dir}")

        if res == 0:
            print(f"{bcolors.OKMAGENTA}Build executed for {build_str}{bcolors.ENDC}")
            build_summary += f"{bcolors.OKMAGENTA}EXECUTED... {build_str}{bcolors.ENDC}\n"
        else:
            build_summary += f"{bcolors.OKRED}ERROR... {build_str}{bcolors.ENDC}\n"

print("\nBuild summary:\n" + build_summary[:-1])
