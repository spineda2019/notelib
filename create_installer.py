from argparse import ArgumentParser, Namespace
from sys import exit as sys_exit, stderr
from shutil import copy2 as shutil_copy2
from os import remove as os_remove
from os.path import exists as os_path_exists
from os.path import realpath as os_path_realpath
from os.path import dirname as os_path_dirname
from subprocess import run as subprocess_run
from subprocess import CompletedProcess


def executable_does_not_exist(build_directory: str) -> bool:
    return not os_path_exists(f"{build_directory}\\notelib.exe")


def clean_installer_directory(installer_directory: str) -> None:
    if (os_path_exists(f"{installer_directory}\\packages\\"
                       "com.spineda.x64installer\\data\\notelib.exe")):
        os_remove(
            f"{installer_directory}\\packages\\"
            "com.spineda.x64installer\\data\\notelib.exe")


def main(args: Namespace) -> int:
    script_directory: str = os_path_dirname(os_path_realpath(__file__))
    build_directory: str = f"{script_directory}\\{args.builddir}"
    installer_directory: str = f"{script_directory}\\{args.installdir}"

    clean_installer_directory(installer_directory)
    if executable_does_not_exist(build_directory):
        print("FATAL: notelib.exe not found. Ensure you have built it",
              file=stderr)
        return -1

    original_executable_path: str = f"{build_directory}\\notelib.exe"
    destination_executable_path: str = (f"{installer_directory}\\packages\\"
                                        "com.spineda.x64installer\\data\\"
                                        "notelib.exe")

    shutil_copy2(original_executable_path, destination_executable_path)

    windeployqt_command = ["windeployqt", "notelib.exe"]
    command_directory: str = (f"{installer_directory}\\packages\\"
                              "com.spineda.x64installer\\data\\")
    print("Generating Installer Dependencies...")
    result: CompletedProcess = subprocess_run(windeployqt_command,
                                              capture_output=True,
                                              text=True,
                                              cwd=command_directory)

    if result.returncode != 0:
        print(f"Unexpected Error: {result}", file=stderr)
        return result.returncode

    package_directory: str = f"{installer_directory}\\packages"
    config_file: str = f"{installer_directory}\\config\\config.xml"
    create_binary_command = ["binarycreator", "--offline-only",
                             "-p", package_directory,
                             "-c", config_file,
                             "NotebookLibraryInstaller.exe"]
    print(f"Generating Installer in {installer_directory}...")
    result: CompletedProcess = subprocess_run(
        create_binary_command,
        capture_output=True,
        text=True,
        cwd=installer_directory)

    return result.returncode


if __name__ == "__main__":
    __doc__ = "Create the installer for the project on windows"
    parser = ArgumentParser(description=__doc__)

    parser.add_argument("-b", "--builddir", type=str, default="build",
                        help="Build directory where the executable resides. "
                        "Defaults to \"build\"")

    parser.add_argument("-i", "--installdir", type=str, default="installer",
                        help="Destination of the installer. "
                        "Defaults to \"installer\"")

    args = parser.parse_args()

    sys_exit(main(args))
