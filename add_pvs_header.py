import os

# The PVS-Studio Free License Header
PVS_HEADER = [
    "// This is a personal academic project. Dear PVS-Studio, please check it.\n"
    "// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com\n\n"
]

EXTENSIONS = {".cpp", ".c", ".h", ".hpp", ".cc", ".cxx"}

def is_header_present(lines):
    if len(lines) < 2:
        return False
    # Check if the first two lines match loosely (ignoring whitespace differences if needed)
    return PVS_HEADER[0].strip() in lines[0] and PVS_HEADER[1].strip() in lines[1]

def process_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        if is_header_present(lines):
            print(f"[SKIP] Header already exists: {filepath}")
            return

        # Prepend header
        new_content = PVS_HEADER + lines
        
        with open(filepath, 'w', encoding='utf-8') as f:
            f.writelines(new_content)
        print(f"[DONE] Added header to: {filepath}")

    except Exception as e:
        print(f"[ERR ] Could not process {filepath}: {e}")

def process_dir(root_dir: str):

    print(f"Scanning directory: {root_dir}")
    
    for subdir, dirs, files in os.walk(root_dir):
        if "build" in dirs: dirs.remove("build")
        if ".git" in dirs: dirs.remove(".git")
        

        for file in files:
            ext = os.path.splitext(file)[1]
            if ext in EXTENSIONS:
                process_file(os.path.join(subdir, file))
                # print(f'process file {os.path.join(subdir, file)}') # dry run


def main():
    src_dirs = [
        'include',
        'src'
    ]
    root_dir = os.getcwd()

    for dir in src_dirs:
        process_dir(os.path.join(root_dir,dir))

if __name__ == "__main__":
    main()