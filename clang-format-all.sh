#!/bin/bash
#
# clang-format-all: a tool to run clang-format on an entire project
# Copyright (C) 2021 Huang Weiyao <jy.cat@qq.com>
# Copyright (C) 2016 Evan Klitzke <evan@eklitzke.org>
#
# Usage: $0 DIR...
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

function progress_bar {
  let _progress=(${1}*100/${2}*100)/100
  let _done=(${_progress}*4)/10
  let _left=40-$_done

  _fill=$(printf "%${_done}s")
  _empty=$(printf "%${_left}s")

  printf "\rProgress($1/$2): [${_fill// /\#}${_empty// /-}] ${_progress}%%"
}

function usage {
  echo "Usage: $0 DIR..."
  exit 1
}

# Variable that will hold the name of the clang-format command
FMT=""

# Some distros just call it clang-format. Others (e.g. Ubuntu) are insistent
# that the version number be part of the command. We prefer clang-format if
# that's present, otherwise we work backwards from highest version to lowest
# version.
for clangfmt in clang-format{,-{4,3}.{9,8,7,6,5,4,3,2,1,0}}; do
  if which "$clangfmt" &>/dev/null; then
    FMT="$clangfmt"
    break
  fi
done

# Check if we found a working clang-format
if [ -z "$FMT" ]; then
    echo "failed to find clang-format"
    exit 1
fi

# Check all of the arguments first to make sure they're all directories
for dir in "$@"; do
  if [ ! -d "${dir}" ]; then
    echo "${dir} is not a directory"
    usage
  fi
done

# Find a dominating file, starting from a given directory and going up.
find_dominating_file() {
  if [ -r "$1"/"$2" ]; then
    return 0
  fi
  if [ "$1" = "/" ]; then
    return 1
  fi
  find_dominating_file "$(realpath "$1"/..)" "$2"
  return $?
}

if [ $# -eq 0 ]; then
  usage
  exit 0
fi

# Run clang-format -i on all of the things
for dir in "$@"; do
  pushd "${dir}" &>/dev/null # cd to $dir

  if ! find_dominating_file . .clang-format; then
    echo "Failed to find dominating .clang-format starting at $PWD"
    continue
  fi

  list=( $(find . \
    -name '*.c' \
    -o -name '*.cc' \
    -o -name '*.cpp' \
    -o -name '*.h' \
    -o -name '*.hh' \
    -o -name '*.hpp') )

  for index in ${!list[@]}; do
    progress_bar $((index+1)) ${#list[@]}
    if [[ -f ${list[index]} ]]; then
      $FMT -i ${list[index]}
    fi
  done

  echo ""

  popd &>/dev/null
done
