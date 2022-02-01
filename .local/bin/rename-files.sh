#!/bin/bash

# USAGE: ./dublicate_clean <DIR>

# These options will stop the script if there are any unexpected errors
set -e
set -o pipefail

# Set the directory that needs to be cleaned, This is the only argument to the script
working_dir=${1:-"."}
cd "$working_dir"

# This function will determine what should be the next latest version the in
# the version files
add_file() {
	moving_file=$1

	last_version=$(ls -1 -- "$version_folder" | sed -E -n '/.*\(([0-9]*)\).*/!{s/.*/0/p;d;} ; s/.*\(([0-9]*)\)(\.[^.]*)?/\1/p' | sort -n | tail -n1)
	if [[ -z "$last_version" ]]; then
		NEW_VERSION=0
	else
		NEW_VERSION=$((last_version+1))
	fi


	# Move the file to the appropriate version name
	if (( NEW_VERSION == 0 )); then
		mv -v -- "$moving_file" "$version_folder/$file_name$file_extension"
	else
		mv -v -- "$moving_file" "$version_folder/$file_name ($NEW_VERSION)$file_extension"
	fi
}

# Iterate through each file, if the file has the pattern of a version file then
# move it into its version folder with the appropirate file_name using the
# add_file function
for file in *; do
	# If the file has version number like pattern then process that file
	regex='(.*) \([0-9]*\)(\.[^.]*)?'
	if [[ $file =~ $regex ]]; then
		echo "Processing file: '$file'"

		# Get the name of the original file from this version
		file_name=${BASH_REMATCH[1]}
		file_extension=${BASH_REMATCH[2]}
		orig_file="$file_name$file_extension"
		version_folder=${orig_file}_VERSIONS
		if [[ ! -d "$version_folder" ]]; then
			mkdir -v -- "$version_folder"
		fi

		# To send the original file into the versions directory first
		# if the original file exists then add it to version directory
		if [ -f "$orig_file" ]; then
			add_file "$orig_file"
		fi
		add_file "$file"
	fi
done
