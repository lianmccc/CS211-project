#!/usr/bin/python
# Filename: display_all_analyzer.py


from mobile_insight.analyzer.analyzer import *
import datetime

__all__ = ["DisplayAllAnalyzer"]


class DisplayAllAnalyzer(Analyzer):

    def __init__(self):
        Analyzer.__init__(self)

        # self.add_source_callback(self.__msg_callback)
        # self.last_bytes = {} # LACI -> bytes <int> Last remaining bytes in MAC UL buffer
        # self.buffer = {} # LCID -> [(sys_fn, sun_fn), packet_bytes] buffered mac ul packets
        # self.ctrl_pkt_sfn = {} # LCID -> [sys_fn, sun_fn] when last mac ul control packet comes
        # self.cur_fn = None # Record current [sys_fn, sub_fn] for mac ul buffer
        # self.cell_id = {} # cell_name -> idx Keep index for each type of cell
        # self.idx = 0 # current recorded cell idx
        # self.failed_harq = [0] * 8 * 3 * 2
        # self.queue_length = 0
        # store every failed_harq by ['timestamp', 'cell_idx', 'harq_id', 'tb_idx', 'tb_size', 'retx_succeed', 'retx_cnt', 'trigger_rlc_retx', 'sn_sfn', 'delay']
        # self.mac_retx = []  # for each retx, get [timestamp, fn_sfn, time, delay]

    def set_source(self, source):
        """
        Set the trace source. Enable the cellular signaling messages

        :param source: the trace source (collector).
        """
        Analyzer.set_source(self, source)


    def __msg_callback(self, msg):

        if msg.type_id == "5G_NR_MAC_PDSCH_Status":
            self.__msg_callback_pdsch_status(msg)

    def __msg_callback_pdsch_status(self, msg):
        log_item = msg.data.decode()
        print(log_item)