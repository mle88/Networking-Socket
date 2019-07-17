make clean
make

echo ""
echo "Creating server and 1 client"
sleep 2

x-terminal-emulator -t SERVER -e ./.server.sh 3000 
sleep 2

x-terminal-emulator -t AERONAUTICS -e ./.client.sh 3000 localhost 
