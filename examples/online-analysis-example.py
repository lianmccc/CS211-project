#!/usr/bin/python
# Filename: offline-analysis-example.py
import os
import sys

"""
Offline analysis by replaying logs
"""

# Import MobileInsight modules
from mobile_insight.monitor import OfflineReplayer
from mobile_insight.analyzer import DisplayAllAnalyzer, MsgLogger, NrRrcAnalyzer, LteRrcAnalyzer, WcdmaRrcAnalyzer, LteNasAnalyzer, UmtsNasAnalyzer, LteMacAnalyzer, LteMeasurementAnalyzer

if __name__ == "__main__":

    # Initialize a monitor
    src = OfflineReplayer()
    src.set_input_path("./logs/diag_log_20221101_141847_68b329da9893e34099c7d8ad5cb9c940_Google-Pixel5_.mi3log.qmdl")
    # src.enable_log_all()
    # src.enable_log("LTE_PHY_Serv_Cell_Measurement")
    # src.enable_log("5G_NR_RRC_OTA_Packet")
    # src.enable_log("LTE_RRC_OTA_Packet")
    # src.enable_log("LTE_NB1_ML1_GM_DCI_Info")
    src.enable_log("5G_NR_MAC_PDSCH_Status")

    logger = MsgLogger()
    logger.set_decode_format(MsgLogger.XML)
    logger.set_dump_type(MsgLogger.FILE_ONLY)
    logger.save_decoded_msg_as("./test.txt")
    logger.set_source(src)

    display_all_analyzer = DisplayAllAnalyzer()
    display_all_analyzer.set_source(src)

    # # Analyzers
    # nr_rrc_analyzer = NrRrcAnalyzer()
    # nr_rrc_analyzer.set_source(src)  # bind with the monitor

    # lte_rlc_analyzer = LteRlcAnalyzer()
    # lte_rlc_analyzer.set_source(src)  # bind with the monitor

    # wcdma_rrc_analyzer = WcdmaRrcAnalyzer()
    # wcdma_rrc_analyzer.set_source(src)  # bind with the monitor

    # lte_nas_analyzer = LteNasAnalyzer()
    # lte_nas_analyzer.set_source(src)

    # umts_nas_analyzer = UmtsNasAnalyzer()
    # umts_nas_analyzer.set_source(src)

    # lte_mac_analyzer = LteMacAnalyzer()
    # lte_mac_analyzer.set_source(src)

    # lte_meas_analyzer = LteMeasurementAnalyzer()
    # lte_meas_analyzer.set_source(src)

    # print lte_meas_analyzer.get_rsrp_list() 
    # print lte_meas_analyzer.get_rsrq_list()

    # Start the monitoring
    src.run()
