#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Ошибка, введите путь к директории"
	exit 1
fi

source=$1
temp_dir=$(mktemp -d)

if [ ! -d "$temp_dir" ]; then
        echo "Ошибка в создании временного каталога"
        exit 1
fi
trap 'rm -rf "$temp_dir" && exit 1' EXIT


if [ ! -f "$source" ]; then
	echo "Исходный файл не существует: $source"
	exit 1
fi

output_com=$(grep '&Output:' "$source" | sed 's/^[[:space:]]*\/\/[[:space:]]*&Output:[[:space:]]*//')

if [ -z "$output_com" ]; then
        echo "Комментарий &Output: в исходном файле не найден"
        exit 1
fi

compiler_com=""
if [[ "$source" == *.c ]]; then
        compiler_com="gcc"
elif [[ "$source" == *.cpp ]]; then
        compiler_com="g++"
else
	echo "Неподдерживаемый тип файла"
	exit 1
fi

"$compiler_com" "$source" -o "${temp_dir}/${output_com}"

mv "${temp_dir}/${output_com}" "$(dirname "$source")"

rm -rf "$temp_dir"

echo "Сборка завершена успешно, конечный файл: $output_com"
