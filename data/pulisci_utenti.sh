#!/bin/bash

# Verifica che il file esista
if [ -f "utenti.dat" ]; then
  > utenti.dat
  echo "✅ File utenti.dat svuotato con successo."
else
  echo "❌ Errore: il file utenti.dat non esiste nella cartella corrente."
fi
