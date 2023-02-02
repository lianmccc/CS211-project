#include "consts.h"
#include "log_packet.h"
#include "log_packet_helper.h"

const Fmt NrMacPdschStatus_Fmt[] = {    //16
    {UINT, "Minor Version",             2},
    {UINT, "Major Version",             2},
    {UINT, "Sleep",                     1},
    {UINT, "Beam Change",               1},
    {UINT, "Signal Change",             1},
    {UINT, "DL Dynamic Cfg Change",     1},
    {UINT, "DL Config",                 1},
    {UINT, "UL Config",                 1},
    {SKIP, NULL,                        2},
    {UINT, "Log Fields Change BMask",   2},
    {UINT, "Sub ID ",                   1},
    {UINT, "Num Records",               1},
};

const Fmt NrMacPdschStatusRecord[] = {  //8
    //System Time
    {UINT, "Slot",                      1},
    {UINT, "Numerology",                1},
    {UINT, "Frame",                     2},
    //Num PDSCH Status
    {UINT, "Num PDSCH Status",          1},
    {SKIP, NULL,                        3},
};

const Fmt NrMacPdschStatusInfo[] = {    //20
    {UINT, "Carrier ID",                0},
    {UINT, "Tech ID to Variant Id",     4}, //?
    {UINT, "Physical cell ID",          4},
    {UINT, "EARFCN",                    0},
    {UINT, "TB Index",                  2},
    {UINT, "TB Size",                   0},
    {SKIP, NULL,                        1},
    {UINT, "SCS MU",                    1},
    {UINT, "MCS",                       0},
    {UINT, "Num Rbs",                   4}, 
    {UINT, "RV",                        0},
    {UINT, "HARQ Or MBSFN Area Id",     0},
    {UINT, "RNTI Type",                 0},
    {UINT, "K1 Or PMCH ID",             0},
    {UINT, "TCI",                       0},
    {UINT, "Num Layers",                0},
    {UINT, "Iteration Index",           0},
    {UINT, "CRC Status",                1},
    {UINT, "New Tx Flag",               0},
    {UINT, "NDI",                       0},
    {UINT, "Discard Mode",              0},
    {UINT, "Bypass Decode",             0},
    {UINT, "Bypass HARQ",               0},
    {UINT, "Num ReTx",                  1},
    {UINT, "HD Onload Timeout",         0},
    {UINT, "HARQ Onload Timeout",       0},
    {UINT, "HD Offload Timeout",        0},
    {UINT, "HARQ Offload Timeout",      0},
    {UINT, "Did Recomb",                0},
    {UINT, "Is IOVec Valid",            1},
    {UINT, "Mod Type",                  0},
    {UINT, "High Clock Mode",           0},
    {UINT, "Num RX",                    0},
    {UINT, "RX Antenna Mapping",        1},
};

static int
_decode_nr_mac_pdsch_status_subpkt(const char *b, int offset, size_t length,
                       PyObject *result) {

    int start = offset;
    int major_ver = _search_result_int(result, "Major Version");
    int minor_ver = _search_result_int(result, "Minor Version");
    bool success = false;

    switch (major_ver) {
        case 2:{
            switch (minor_ver){
                case 5:{
                    int n_record = _search_result_int(result, "Num Records");
                    PyObject *result_allrecords = PyList_New(0);
                    PyObject *t = NULL;

                    // loop for records
                    for(int i = 0; i < n_record; i++){
                        PyObject *result_record = PyList_New(0);
                        offset += _decode_by_fmt(NrMacPdschStatusRecord,
                                                 ARRAY_SIZE(NrMacPdschStatusRecord, Fmt),
                                                 b, offset, length, result_record);

                        // loop for PDSCH Status
                        int n_status = _search_result_int(result_record, "Num PDSCH Status");
                        for(int i = 0; i < n_status; i++){
                            PyObject *result_status = PyList_New(0);
                            offset += _decode_by_fmt(NrMacPdschStatusInfo,
                                                 ARRAY_SIZE(NrMacPdschStatusInfo, Fmt),
                                                 b, offset, length, result_status);

                            // Physical cell ID, EARFCN
                            uint group = _search_result_uint(result_status, "Physical cell ID");

                            uint field0 = ((1 << 10) - 1) & group;
                            uint field1 = (group >> 10);

                            PyObject *old_object = _replace_result_int(result_status, "Physical cell ID", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "EARFCN", field1);
                            Py_DECREF(old_object);

                            // TB Index, TB Size
                            group = _search_result_uint(result_status, "TB Index");

                            field0 = ((1 << 5) - 1) & group;
                            field1 = (group >> 5);

                            old_object = _replace_result_int(result_status, "TB Index", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "TB Size", field1);
                            Py_DECREF(old_object);

                            // SCS MU, MCS
                            group = _search_result_uint(result_status, "SCS MU");

                            field0 = ((1 << 2) - 1) & group;
                            field1 = (group >> 2);

                            old_object = _replace_result_int(result_status, "SCS MU", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "MCS", field1);
                            Py_DECREF(old_object);

                            // Num Rbs, RV, HARQ Or MBSFN Area Id, RNTI Type, K1 Or PMCH ID, TCI, Num Layers, Iteration Index
                            group = _search_result_uint(result_status, "Num Rbs");

                            field0 = ((1 << 9) - 1) & group;
                            field1 = ((1 << 2) - 1) & (group >> 9);
                            uint field2 = ((1 << 9) - 1) & (group >> 11);
                            uint field3 = ((1 << 2) - 1) & (group >> 20);
                            uint field4 = ((1 << 4) - 1) & (group >> 22);
                            uint field5 = ((1 << 2) - 1) & (group >> 26);
                            uint field6 = ((1 << 2) - 1) & (group >> 28);
                            uint field7 = (group >> 30);

                            old_object = _replace_result_int(result_status, "Num Rbs", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "RV", field1);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "HARQ Or MBSFN Area Id", field2);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "RNTI Type", field3);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "K1 Or PMCH ID", field4);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "TCI", field5);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Num Layers", field6);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Iteration Index", field7);
                            Py_DECREF(old_object);

                            // CRC Status, New Tx Flag, NDI, Discard Mode, Bypass Decode, Bypass HARQ
                            group = _search_result_uint(result_status, "CRC Status");

                            field0 = ((1 << 1) - 1) & group;
                            field1 = ((1 << 1) - 1) & (group >> 1);
                            field2 = ((1 << 3) - 1) & (group >> 2);
                            field3 = ((1 << 1) - 1) & (group >> 5);
                            field4 = ((1 << 1) - 1) & (group >> 6);
                            field5 = (group >> 7);

                            old_object = _replace_result_int(result_status, "CRC Status", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "New Tx Flag", field1);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "NDI", field2);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Discard Mode", field3);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Bypass Decode", field4);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Bypass HARQ", field5);
                            Py_DECREF(old_object);

                            // Num ReTx, HD Onload Timeout, HARQ Onload Timeout, HD Offload Timeout, HARQ Offload Timeout, Did Recomb
                            group = _search_result_uint(result_status, "Num ReTx");

                            field0 = ((1 << 3) - 1) & group;
                            field1 = ((1 << 1) - 1) & (group >> 3);
                            field2 = ((1 << 1) - 1) & (group >> 4);
                            field3 = ((1 << 1) - 1) & (group >> 5);
                            field4 = ((1 << 1) - 1) & (group >> 6);
                            field5 = (group >> 7);

                            old_object = _replace_result_int(result_status, "Num ReTx", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "HD Onload Timeout", field1);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "HARQ Onload Timeout", field2);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "HD Offload Timeout", field3);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "HARQ Offload Timeout", field4);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Did Recomb", field5);
                            Py_DECREF(old_object);

                            // Is IOVec Valid, Mod Type, High Clock Mode, Num RX
                            group = _search_result_uint(result_status, "Is IOVec Valid");

                            field0 = ((1 << 2) - 1) & group;
                            field1 = ((1 << 3) - 1) & (group >> 2);
                            field2 = ((1 << 1) - 1) & (group >> 5);
                            field3 = (group >> 7);

                            old_object = _replace_result_int(result_status, "Is IOVec Valid", field0);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Mod Type", field1);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "High Clock Mode", field2);
                            Py_DECREF(old_object);
                            old_object = _replace_result_int(result_status, "Num RX", field3);
                            Py_DECREF(old_object);



                            char name[64];
                            sprintf(name, "Status[%d]", i);
                            t = Py_BuildValue("(sOs)", name, result_status, "dict");

                            PyList_Append(result_record, t);

                            Py_DECREF(result_status);
                            Py_DECREF(t);
                        }

                        char name[64];
                        sprintf(name, "Records[%d]", i);
                        t = Py_BuildValue("(sOs)", name, result_record, "dict");

                        PyList_Append(result_allrecords, t);

                        Py_DECREF(result_record);
                        Py_DECREF(t);
                    }

                    t = Py_BuildValue("(sOs)", "Records", result_allrecords, "list");
                    PyList_Append(result, t);
                    Py_DECREF(t);
                    Py_DECREF(result_allrecords);

                    success = true;
                    break;
                }
                default:
                    break;
            }  
        }
        default:
            break;
    }

    if(!success){
        printf("Unknown 5G NR MAC PDSCH STATUS: %d.%d\n", major_ver, minor_ver);
    }

    return offset - start;
}