#ifndef __NMX_READOUT_WRAPPER
#define __NMX_READOUT_WRAPPER

#ifdef __cplusplus
extern "C" {
#endif
  struct nmx_readout;
  typedef struct nmx_readout nmx_readout_t;

  // Create a new BIFROST Readout object
  nmx_readout_t * nmx_readout_create(char* address, int port);

  // Destroy an existing BIFROST Readout object
  void nmx_readout_destroy(nmx_readout_t* br);

  // Add a readout value to the transmission buffer of the BIFROST Readout object
  // Automatically transmits the packet if it is full.
  void nmx_readout_add(
      nmx_readout_t* br, uint8_t Ring, uint8_t FEN, uint32_t TimeHigh, uint32_t TimeLow,
                 uint8_t VMM, uint8_t Channel
  );
  // Send the current data buffer for the BIFROST Readout object
  void nmx_readout_send(nmx_readout_t* br);
  // Update the pulse and previous pulse times for the BIFROST Readout object
  void nmx_readout_setPulseTime(
      nmx_readout_t* br, uint32_t pulse_high, uint32_t pulse_low,
      uint32_t prev_high, uint32_t prev_low
  );
  // Initialize a new packet with no readouts for the BIFROST Readout object
  void nmx_readout_newPacket(nmx_readout_t* br);

#ifdef __cplusplus
}
#endif

#endif
