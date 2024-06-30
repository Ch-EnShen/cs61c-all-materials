#!/usr/bin/env python3

import xml.etree.ElementTree as ET
import argparse
import os
import re
import subprocess
import sys

ASM_FILE_EXTENSION = ".s"
VENUS_TRACE_PATTERN = "%1%\t%2%\t%5%\t%6%\t%7%\t%8%\t%9%\t%10%\t%pc%\t%inst%\t%line%\n"

script_dir = os.path.realpath(sys.path[0])
logisim_path = os.path.join(script_dir, "../../../logisim-evolution.jar")
venus_path = os.path.join(script_dir, "../../../venus-cs61c-su20-proj3.jar")

def main(asm_file_paths, num_cycles):
  error_log_path = os.path.join(script_dir, "error.log")

  for asm_file_path in asm_file_paths:
    asm_filename = os.path.basename(asm_file_path)
    # Check file extension
    if not asm_filename.endswith(ASM_FILE_EXTENSION):
      print("Invalid assembly file: %s (file extension mismatch)" % asm_filename)
      continue

    # Generate filepaths
    input_slug = asm_filename[:-len(ASM_FILE_EXTENSION)]
    test_slug = "cpu-%s" % input_slug

    asm_file_path = os.path.join(os.getcwd(), asm_file_path)
    hex_data_path = os.path.join(script_dir, "inputs/%s.hex" % input_slug)
    reference_output_path = os.path.join(script_dir, "reference_output/%s-ref.out" % test_slug)
    run_circ_path = os.path.join(script_dir, "../../../run.circ")
    test_circ_path = os.path.join(script_dir, "%s.circ" % test_slug)

    print("Generating test for %s..." % test_slug)

    # Generate reference output
    test_num_cycles = num_cycles
    venus_cmd = ["java", "-jar", venus_path, asm_file_path, "-it", "-t", "-ti", "-tp", VENUS_TRACE_PATTERN, "-ts", "-ur"]
    if num_cycles > -1:
      venus_cmd.append("-tn")
      venus_cmd.append(str(num_cycles + 1))
    try:
      with open(reference_output_path, "w") as stdout, open(error_log_path, "w") as stderr:
        proc = subprocess.Popen(venus_cmd, cwd=script_dir, stdout=stdout, stderr=stderr)
        proc.wait()
      with open(reference_output_path, "r+") as reference_output_file:
        reference_output = reference_output_file.read()
        if proc.returncode != 0 or "[ERROR]" in reference_output:
          print("Venus errored when generating reference output for %s!" % test_slug)
          print("-----From stdout-----")
          print(reference_output)
          print("-----From stderr-----")
          try:
            with open(error_log_path, "r") as error_log_file:
              print(error_log_file.read())
          except Exception as e:
            print(e)
          continue

        # Cleanup reference output
        reference_output = re.sub("\n\n+", "\n", reference_output)
        if test_num_cycles == -1:
          test_num_cycles = reference_output.strip().count("\n") + 1
        reference_output_file.seek(0)
        reference_output_file.write(reference_output)
        reference_output_file.truncate()
    except Exception as e:
      print(e)
      print("Error generating reference output, skipping %s" % test_slug)
      continue
    print("  Generated reference output (cycles: %d)" % test_num_cycles)

    # Generate machine code
    instruction_strs = None
    venus_cmd = ["java", "-jar", venus_path, "-d", asm_file_path]
    try:
      with open(hex_data_path, "w") as stdout, open(error_log_path, "w") as stderr:
        proc = subprocess.Popen(venus_cmd, cwd=script_dir, stdout=stdout, stderr=stderr)
        proc.wait()
      with open(hex_data_path, "r") as hex_data_file:
        hex_data = hex_data_file.read()
        if proc.returncode != 0 or "[ERROR]" in hex_data:
          print("Venus errored when generating machine code for %s!" % test_slug)
          print("-----From stdout-----")
          print(hex_data)
          print("-----From stderr-----")
          try:
            with open(error_log_path, "r") as error_log_file:
              print(error_log_file.read())
          except Exception as e:
            print(e)
          continue

        instruction_strs = hex_data.strip().split("\n")
    except Exception as e:
      print(e)
      print("Error generating machine code, skipping %s" % test_slug)
      continue
    print("  Generated machine code")

    # Generate test circuit
    try:
      rom_instructions = ""
      for instruction_str in instruction_strs:
        # Chop off 0x prefix
        if instruction_str.startswith("0x"):
          instruction_str = instruction_str[2:]
        rom_instructions += instruction_str + " "
      rom_instructions = rom_instructions[:-1] + "\n"

      tree = ET.parse(run_circ_path)
      root = tree.getroot()
      circuit = root.find("circuit")

      ROM = circuit.find("./comp/[@name='ROM']")
      ROM[2].text = "addr/data: 14 32\n" + rom_instructions

      constant = circuit.find("./comp/[@name='Constant']")
      constant[1].attrib["val"] = hex(test_num_cycles)

      cpu_lib = root.find("./lib/[@desc='file#cpu.circ']")
      cpu_lib.attrib["desc"] = "file#../../../cpu.circ"

      tree.write(test_circ_path)
    except Exception as e:
      print(e)
      print("Error generating test circuit, skipping %s" % test_slug)
      continue

    print("  Created test %s!" % test_slug)

if __name__ == "__main__":
  parser = argparse.ArgumentParser(description="Create custom CPU tests")
  parser.add_argument("tests", nargs="+", help="Paths to RISC-V assembly files (ending in \".s\") you want to create tests for")
  parser.add_argument("-n", type=int, default=-1, help="How many cycles you want to simulate the CPU for (default is the number of cycles Venus takes to run your code)")
  args = parser.parse_args()

  main(args.tests, args.n)
