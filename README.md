nr_mac_pdsch_status 
==============


## How to Run

Simply run `./install-ubuntu.sh` to recompile and run offline-analysis-example.py, offline-analysis-example.py will take the log file, using 5G_NR_MAC_PDSCH_Status decoder to decode the message and give the result to a display all analyzer, outputing decoded packets in python dict format.

a sample decoded output will look like

`{'log_msg_len': 56, 'type_id': '5G_NR_MAC_PDSCH_Status', 'timestamp': datetime.datetime(2022, 11, 1, 21, 19, 42, 81765), 'Minor Version': 5, 'Major Version': 2, 'Sleep': 0, 'Beam Change': 0, 'Signal Change': 0, 'DL Dynamic Cfg Change': 0, 'DL Config': 0, 'UL Config': 0, 'Log Fields Change BMask': 0, 'Sub ID ': 0, 'Num Records': 1, 'Records': [{'Slot': 6, 'Numerology': 0, 'Frame': 255, 'Num PDSCH Status': 1, 'Status[0]': {'Carrier ID': 0, 'Tech ID to Variant Id': 35192577, 'Physical cell ID': 537, 'EARFCN': 174770, 'TB Index': 0, 'TB Size': 277, 'SCS MU': 0, 'MCS': 7, 'Num Rbs': 4, 'RV': 0, 'HARQ Or MBSFN Area Id': 8, 'RNTI Type': 0, 'K1 Or PMCH ID': 4, 'TCI': 0, 'Num Layers': 2, 'Iteration Index': 0, 'CRC Status': 1, 'New Tx Flag': 1, 'NDI': 0, 'Discard Mode': 0, 'Bypass Decode': 0, 'Bypass HARQ': 0, 'Num ReTx': 0, 'HD Onload Timeout': 0, 'HARQ Onload Timeout': 0, 'HD Offload Timeout': 0, 'HARQ Offload Timeout': 0, 'Did Recomb': 0, 'Is IOVec Valid': 1, 'Mod Type': 1, 'High Clock Mode': 0, 'Num RX': 0, 'RX Antenna Mapping': 0}}]}`
