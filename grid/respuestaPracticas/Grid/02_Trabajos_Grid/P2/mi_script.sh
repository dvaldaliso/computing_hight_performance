echo $(date +"%T")
echo "El primer argumento es: $1"
for arg in "$@"; do
    echo "Argumento: $arg"
done
