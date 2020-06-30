rm bin/ElizaHead
rm bin/ElizaServer
rm bin/Bot
gcc src/ElizaHead.c src/eliza.c -o bin/ElizaHead
gcc src/ElizaServer.c src/eliza.c -o bin/ElizaServer
gcc src/bot.c src/eliza.c -o bin/Bot
