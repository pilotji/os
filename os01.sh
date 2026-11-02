#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo
    echo "1. Create address book"
    echo "2. View address book"
    echo "3. Insert a record"
    echo "4. Delete a record"
    echo "5. Modify a record"
    echo "6. Exit"

    read -p "Enter your choice: " ch

    case $ch in
        1)
            > "$FILE"
            echo "Address book created."
            ;;

        2)
            if [ -s "$FILE" ]; then
                cat "$FILE"
            else
                echo "Address book is empty."
            fi
            ;;

        3)
            read -p "Enter name: " name
            read -p "Enter phone: " phone
            read -p "Enter address: " address
            echo "$name|$phone|$address" >> "$FILE"
            echo "Record inserted."
            ;;

        4)
            read -p "Enter name to delete: " name
            if grep -q "^$name|" "$FILE" 2>/dev/null; then
                grep -v "^$name|" "$FILE" > temp.txt
                mv temp.txt "$FILE"
                echo "Record deleted."
            else
                echo "Record not found."
            fi
            ;;

        5)
            read -p "Enter name to modify: " name
            if grep -q "^$name|" "$FILE" 2>/dev/null; then
                read -p "Enter new phone: " phone
                read -p "Enter new address: " address

                awk -F'|' -v n="$name" -v p="$phone" -v a="$address" \
                'BEGIN {OFS="|"} $1==n {$2=p; $3=a} {print}' "$FILE" > temp.txt

                mv temp.txt "$FILE"
                echo "Record modified."
            else
                echo "Record not found."
            fi
            ;;

        6)
            echo "Exiting..."
            exit
            ;;

        *)
            echo "Invalid choice."
            ;;
    esac
done
