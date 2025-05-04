#!/bin/bash

function isPalindrome() {
  local str="$1"
  local lower=$(echo "$str" | tr '[:upper:]' '[:lower:]')
  local reversed=$(echo "$lower" | rev)
  if [ "$lower" == "$reversed" ]; then
    echo 1
  else
    echo 0
  fi
}

read -p "Enter a string: " str
isPalindrome "$str"
