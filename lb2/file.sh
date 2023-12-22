#!/bin/sh

# Функция для получения первого доступного имени файла (001, 002 и тд)
first_filename() {
    i=1
    while true; do
        # Преобразование числа в строку с ведущими нулями
        file=$(printf "%03d" $i) 
        # Проверка на существование файла
        if [ ! -e "/shareVol/$file" ]; then 
            # Вывод имени файла, если он не существует
            printf "%03d" $i 
            break
        fi
        # Иначе увеличение счетчика
        i=$((i+1)) 
    done
}

# Функция записи в файл индентификатора контейнера и порядковый номер файла
id_cont_file() {
    local file=$1
    
    # Генерация случайного идентификатора из 12 символов
    local id=$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c 12) 

    # Вывод идентификатора контейнера и порядковый номер файла
    echo "Container id: $id, Filename: $file"
    
    # Запись идентификатора контейнера и порядковый номер файла  
    echo "$id-$file" > "/shareVol/$file"

}

# Функция удаления файла
cleanup_file() {
    local file=$1
    # Вывод сообщения об удалении файла
    echo "Deleted $file"
    # Удаление файла
    rm "/shareVol/$file" 
}

while true; do
    # Блокировка файла
    exec 5>/shareVol/lockfile
    flock -x 5

    file=$(first_filename)
    id_cont_file "$file"
    
    # Снятие блокировки
    exec 5<&-
    # Пауза в 1 секунду
    sleep 1
    cleanup_file "$file"

    echo
    # Пауза в 1 секунду
    sleep 1 
    
done
