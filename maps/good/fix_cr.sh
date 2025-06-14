#!/bin/bash

# Dossier où se trouvent les fichiers
DIR="maps/good"

# Parcourt tous les fichiers .cub dans le dossier
for file in "$DIR"/*.cub; do
    echo "Traitement de $file"
    # Supprime tous les caractères \r (retour chariot)
    sed -i 's/\r//g' "$file"
done

echo "Tous les fichiers ont été corrigés !"
