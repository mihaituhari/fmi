#!/bin/bash

echo -e "\n🧪  Running PHPUnit with coverage...\n"
composer test-coverage

if [ $? -eq 0 ]; then
  echo -e "\n✅ PHPUnit coverage passed!\n"
else
  echo -e "\n❌ PHPUnit coverage failed!\n"
  exit 1
fi

echo -e "\n🔍 Running PHPStan static analysis...\n"
composer static-phpstan

if [ $? -eq 0 ]; then
  echo -e "\n✅ PHPStan passed!\n"
else
  echo -e "\n❌ PHPStan found issues!\n"
  exit 1
fi

echo -e "\n🔎 Running Psalm static analysis...\n"
composer static-psalm

if [ $? -eq 0 ]; then
  echo -e "\n✅ Psalm passed!\n"
else
  echo -e "\n❌ Psalm found issues!\n"
  exit 1
fi

echo -e "\n🧬 Running Mutation Testing with Infection...\n"
composer mutation

if [ $? -eq 0 ]; then
  echo -e "\n✅ Infection mutation testing passed!\n"
else
  echo -e "\n❌ Infection found undetected mutants!\n"
  exit 1
fi

echo -e "\n🎉 All checks passed successfully!"
