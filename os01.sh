
#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo
    echo "========== ADDRESS BOOK =========="
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert a Record"
    echo "4. Delete a Record"
    echo "5. Modify a Record"
    echo "6. Exit"
    echo "=================================="
    read -p "Enter your choice: " ch

    case $ch in

    1)
        > "$FILE"
        echo "Address Book Created Successfully!"
        ;;

    2)
        if [ -s "$FILE" ]; then
            echo
            echo "Name        Phone       Email"
            cat "$FILE"
        else
            echo "Address Book is Empty!"
        fi
        ;;

    3)
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        read -p "Enter Email: " email

        echo "$name | $phone | $email" >> "$FILE"
        echo "Record Inserted Successfully!"
        ;;

    4)
        read -p "Enter Name to Delete: " name

        if grep -q "^$name |" "$FILE" 2>/dev/null; then
            grep -v "^$name |" "$FILE" > temp.txt
            mv temp.txt "$FILE"
            echo "Record Deleted Successfully!"
        else
            echo "Record Not Found!"
        fi
        ;;

    5)
        read -p "Enter Name to Modify: " name

        if grep -q "^$name |" "$FILE" 2>/dev/null; then
            read -p "Enter New Phone: " phone
            read -p "Enter New Email: " email

            grep -v "^$name |" "$FILE" > temp.txt
            echo "$name | $phone | $email" >> temp.txt
            mv temp.txt "$FILE"

            echo "Record Modified Successfully!"
        else
            echo "Record Not Found!"
        fi
        ;;

    6)
        echo "Exiting Address Book..."
        exit 0
        ;;

    *)
        echo "Invalid Choice! Try Again."
        ;;

    esac
done
