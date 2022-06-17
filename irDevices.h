typedef struct iRCommand{
  String commandName;
  uint64_t irCode;
};

typedef struct irDevice{
  String deviceName;
  decode_type_t protocol;
  uint16_t nbits;
  iRCommand irCommand[50];
};

// Add ir codes to this device array
irDevice devices[] = {
  {
    "MHC-EX5", SONY, 12, {
      {"mute-20db", 0x281},
      {"sleep", 0x61},
      {"power", 0xA81},
      {"tape1", 0xC41},
      {"tape2", 0x241},
      {"aux", 0xB81},
      {"deckA-left", 0xEC1},
      {"deckA-right", 0x4C1},
      {"deckA-stop", 0x1C1},
      {"deckA-rewind", 0xCC1},
      {"deckA-fforward", 0x2C1},
      {"deckB-left", 0x4E},
      {"deckB-right", 0x58E},
      {"deckB-stop", 0x18E},
      {"deckB-rewind", 0xD8E},
      {"deckB-fforward", 0x38E},
      {"md-previous", 0x5E},
      {"md-next", 0x85E},
      {"md", 0x961},
      {"md-play", 0x55E},
      {"md-pause", 0x95E},
      {"md-stop", 0x15E},
      {"md-display", 0x19E},
      {"cd-previous", 0xD1},
      {"cd-next", 0x8D1},
      {"cd-repeat", 0x351},
      {"cd", 0xA41},
      {"cd-play", 0x4D1},
      {"cd-pause", 0x9D1},
      {"cd-stop", 0x1D1},
      {"cd-time", 0x151},
      {"tuner", 0x841},
      {"tuner-band", 0xF16},
      {"tuner-minus", 0x896},
      {"tuner-plus", 0x96},
      {"tuner-display", 0xD36},
      {"number1", 0x11},
      {"number2", 0x811},
      {"number3", 0x411},
      {"number4", 0xC11},
      {"direct", 0x146},
      {"number5", 0x211},
      {"number6", 0xA11},
      {"number7", 0x611},
      {"number8", 0xE11},
      {"volume-up", 0x481},
      {"number9", 0x111},
      {"number10", 0x51},
      {"number-big", 0xE51},
      {"volume-down", 0xC81}
    }
  },{
    "samsungtv", SAMSUNG, 32, {
      {"power", 0xE0E040BF},
      {"next", 0xE0E048B7},
      {"previous", 0xE0E008F7}
    }
  }
};
