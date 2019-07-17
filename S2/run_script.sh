make clean
make

echo ""
echo "Creating server and 3 clients"
sleep 2

x-terminal-emulator -t SERVER -e ./.server.sh 3000 
sleep 2

x-terminal-emulator -t AERONAUTICS -e ./.client.sh 3000 localhost sample_aeronautics.txt
sleep 4
x-terminal-emulator -t LA_CASA -e ./.client.sh 3000 localhost sample_la_casa.txt
sleep 4
x-terminal-emulator -t BROTHERS -e ./.client.sh 3000 localhost sample_brothers.txt
