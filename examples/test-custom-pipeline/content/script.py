#!/usr/bin/env python3

import os
from os import path

"""
Checks if a PRIME file was written and it's matching the current platform
Ignores the PRIME file if SilVerPLuM forces priming
"""
def already_primed():
	
	forced = (os.environ["SILVERPLUM_FORCE_PRIME"] == "true")
	platform = os.environ["STARDEWVALLEY_PLATFORM"]
	
	print("Priming was forced" if forced else "Priming was not forced")
	
	if forced:
		return False
	
	expected_prime_file_content = "PRIME_" + platform
	already_primed = False
	
	if os.path.isfile("PRIME"):
		prime_file = open("PRIME", "r")
		already_primed = (prime_file.readline().strip() == expected_prime_file_content)
		prime_file.close()
		
	return already_primed
	
"""
Writes the PRIME file that indicates for a next run that priming is not needed
"""
def write_prime_file():
	
	platform = os.environ["STARDEWVALLEY_PLATFORM"]
	prime_file_content = "PRIME_" + platform
	
	prime_file = open("PRIME", "w")
	prime_file.write(prime_file_content)
	prime_file.close()
	

def main():
	
	if already_primed():
		print("Already primed. Skipping.")
		return
	
	print("Following evironment variables are available:")
	
	for key in os.environ:
		
		print(key + "\t" + os.environ[key])
		
	write_prime_file()
	
main() 
