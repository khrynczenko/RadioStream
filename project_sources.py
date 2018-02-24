import os
from typing import Tuple, List

def print_files_paths(directory : os.PathLike):
    for root, _, files in os.walk(directory):
        for file in files:
            print(os.path.join(root, file).replace("\\", "/"))

if __name__ == "__main__":
    print_files_paths("include")
    print_files_paths("src")