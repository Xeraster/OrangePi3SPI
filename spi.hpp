//halts polling and sends a byte to the spi slave
void spiSendByte(unsigned char commandByte, unsigned char cdata, gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck)
{
    string word = intToBinary(commandByte);//make it easier to serialize
    string worddata = intToBinary(cdata);//make it easier to serialize
    //cout << "word = " << word << endl;
    //cout << "worddata = " << worddata << endl;
    bool exit = false;
    bool aaa = true;//i have no idea what to call this variable but trust me, this is better than what it used to be called
    //set aaa to trrue to allowe enough time for it to set the lines to valid stuff and not miss the first bit
    
    int commandCtr = 0;
    int dataCtr = 0;
    int ctr = 0;//a way to terminate a runaway loop
    while (!exit)
    {
        //page 22 of ICE40 Programming and Configuration has a good spi example


        //send the command byte first
        if (commandCtr < 8 && !aaa)//only do stuff on falling edge of sck
        {
            gpiod_line_set_value(sdo, (word[commandCtr]-48));
            //cout << "writing " << (word[commandCtr]-48) << " to serial" << endl;
            commandCtr++;
        }
        //send the data byte after that
        else if (commandCtr >= 8 && dataCtr < 8 && !aaa)//only do stuff on falling edge of sck
        {
            /* code */
            gpiod_line_set_value(sdo, (worddata[dataCtr]-48));
            //cout << "writing " << (worddata[dataCtr]-48) << " to serial" << endl;
            dataCtr++;
        }

        //generate the sck signal by going up and down a lot. dp this part AFTER the data part
        if (aaa)
        {
            aaa = false;
            gpiod_line_set_value(sck, 0);
        }
        else if (!aaa)
        {
            aaa = true;
            gpiod_line_set_value(sck, 1);
        }
        

        if (ctr >= 10000 | dataCtr >= 8)
        {
            exit = true;
            //cout << "exiting spi loop because ctr >= 10000. commandCtr = " << commandCtr << ". dataCtr = " << dataCtr << endl;
        }
        else if (!aaa)//try only incrementing the counter when sck is low
        {
            ctr++;
        }
        usleep(2);//are such speeds even possible?
    }

    //make sure it reverts to zero when done
    gpiod_line_set_value(sck, 0);
}

// halts polling and sends a byte to the spi slave. This variant only sends a command byte with no data, for commands with no parameters such as reset 0xFF
void spiSendByte(unsigned char commandByte, gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck)
{
    string word = intToBinary(commandByte); // make it easier to serialize
    //cout << "word = " << word << endl;
    bool exit = false;
    bool aaa = true;//i have no idea what to call this variable but trust me, this is better than what it used to be called
    //set aaa to trrue to allowe enough time for it to set the lines to valid stuff and not miss the first bit
    int commandCtr = 0;
    int dataCtr = 0;
    int ctr = 0; // a way to terminate a runaway loop
    while (!exit)
    {
        // page 22 of ICE40 Programming and Configuration has a good spi example

        // send the command byte first
        if (commandCtr < 8 && !aaa) // only do stuff on falling edge of sck
        {
            gpiod_line_set_value(sdo, (word[commandCtr] - 48));
            //cout << "writing " << (word[commandCtr] - 48) << " to serial" << endl;
            commandCtr++;
        }

        // generate the sck signal by going up and down a lot
        if (aaa)
        {
            aaa = false;
            gpiod_line_set_value(sck, 0);
        }
        else if (!aaa)
        {
            aaa = true;
            gpiod_line_set_value(sck, 1);
        }

        if (ctr >= 10000 | commandCtr >= 8)
        {
            exit = true;
            //cout << "exiting spi loop because ctr >= 10000. commandCtr = " << commandCtr << endl;
        }
        else if (!aaa) // try only incrementing the counter when sck is low
        {
            ctr++;
        }
        usleep(2); // are such speeds even possible?
    }

    //make sure it reverts to zero when done
    gpiod_line_set_value(sck, 0);
}

//this polls the input until it read 8 bits then it returns that byte
unsigned char spiReadByte(gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck)
{
    bool exit = false;
    bool aaa = false;
    int ctr = 0;
    string bits = "";
    while (!exit)
    {
        if (aaa)
        {
            aaa = false;
            gpiod_line_set_value(sck, 0);
        }
        else if (!aaa)
        {
            aaa = true;
            gpiod_line_set_value(sck, 1);
        }

        if (!aaa)
        {
            int thisBit = gpiod_line_get_value(sdi);
            bits += to_string(thisBit);
            ctr++;
        }

        if (ctr >= 8)
        {
            exit = true;
        }

        usleep(2);
    }

    //use this, iirc it converts to the correct endianness but i dont remember what that is. its the one that goes like this: b7 b6 b5 b4 b3 b2 b1 b0
    string hexInput = binaryStringToHex(bits, true);
    //cout << "hex input = " << hexInput << endl;
    unsigned char result = (unsigned char)stoi(hexInput);

    return result;//there that should do it
}

//figures out if there is a byte or not. returns 0 if there is no start bit, returns 1 if a start bit was detected
int spiPollStatus(gpiod_chip *chip, gpiod_line *sdo, gpiod_line *sdi, gpiod_line *sck)
{
    return 0;//placeholder return so the compiler wont complain
}