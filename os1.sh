
#!/bin/bash

echo "Enter filename:"
read filename

while [ -z "$filename" ]
do
    echo "Filename cannot be empty. Enter filename:"
    read filename
done

while true
do
    echo ""
    echo "1. Create a File"
    echo "2. Add data in File"
    echo "3. Display content of file"
    echo "4. Search a record"
    echo "5. Delete a record"
    echo "6. Modify record"
    echo "7. Exit"

    echo "Enter choice:"
    read choice

    case $choice in

        1)
            touch "$filename"
            echo "File created."
            ;;

        2)
            echo "Enter emp id, empname and dept:"
            read empid empname dept

            if grep -q "^$empid " "$filename" 2>/dev/null; then
                echo "Record with this ID already exists."
            else
                echo "$empid $empname $dept" >> "$filename"
                echo "Record added."
            fi
            ;;

        3)
            echo "Content of file:"
            cat "$filename"
            ;;

        4)
            echo "Enter employee name to search:"
            read name

            echo "Search results:"
            grep -i "$name" "$filename"
            ;;

        5)
            echo "Enter employee name to delete:"
            read name

            sed -i "/$name/d" "$filename"
            echo "Record deleted."
            ;;

        6)
            echo "Enter employee name to modify:"
            read name

            sed -i "/$name/d" "$filename"

            echo "Enter new details (empid empname dept):"
            read empid empname dept

            echo "$empid $empname $dept" >> "$filename"
            echo "Record modified."
            ;;

        7)
            echo "Exiting..."
            break
            ;;

        *)
            echo "Invalid choice."
            ;;

    esac
done
