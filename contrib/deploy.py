import argparse
import subprocess
import sys
import os

FILES_TO_EXTRAS = ["box.py", "toolchanger.py", "box_protocol.py", "rs485_sniffer.py"]
FILES_TO_CONFIG = ["box.cfg"]
REMOTE_EXTRAS_PATH = "/mnt/UDISK/root/klipper/klippy/extras/"
REMOTE_CONFIG_PATH = "/mnt/UDISK/root/printer_data/config/"

def run_cmd(cmd):
    print(f"Running: {' '.join(cmd)}")
    try:
        subprocess.check_call(cmd)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {e}")
        sys.exit(1)

def main():
    parser = argparse.ArgumentParser(description="Deploy Box Driver to Klipper")
    parser.add_argument("host", nargs="?", default="k2", help="SSH host (default: k2)")
    args = parser.parse_args()
    
    host = args.host
    print(f"Deploying to {host}...")

    # Validate files exist
    all_files = FILES_TO_EXTRAS + FILES_TO_CONFIG
    for f in all_files:
        if not os.path.exists(f):
            print(f"Error: File '{f}' not found in current directory.")
            sys.exit(1)

    # Deploy extras
    print("Deploying Python modules...")
    cmd_extras = ["scp"] + FILES_TO_EXTRAS + [f"{host}:{REMOTE_EXTRAS_PATH}"]
    run_cmd(cmd_extras)

    # Deploy config
    print("Deploying Config...")
    cmd_config = ["scp"] + FILES_TO_CONFIG + [f"{host}:{REMOTE_CONFIG_PATH}"]
    run_cmd(cmd_config)

    # Cleanup and Restart
    print("Cleaning up pyc files and restarting Klipper...")
    # Using unix-style paths for remote machine
    pyc_files = " ".join([f"{REMOTE_EXTRAS_PATH}{f}c" for f in FILES_TO_EXTRAS])
    
    # Construct remote command
    remote_cmd = (
        f"rm -f {pyc_files} && "
        "/etc/init.d/klipper restart"
    )
    
    cmd_ssh = ["ssh", host, remote_cmd]
    run_cmd(cmd_ssh)

    print("Deployment Complete!")

if __name__ == "__main__":
    main()
