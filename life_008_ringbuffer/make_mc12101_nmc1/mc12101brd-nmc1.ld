MEMORY
{
  C0_IMU0 : ORIGIN = 0x00000800, LENGTH = 0x0001F800
  C0_IMU1 : ORIGIN = 0x00020000, LENGTH = 0x00020000
  C0_IMU2 : ORIGIN = 0x00040000, LENGTH = 0x00020000
  C0_IMU3 : ORIGIN = 0x00060000, LENGTH = 0x00020000
  SHMEM0 : ORIGIN = 0x00280000, LENGTH = 0x00040000
  SHMEM1 : ORIGIN = 0x002C0000, LENGTH = 0x00040000
  EMI : ORIGIN = 0x80000000, LENGTH = 0x20000000
  SYNCRO : ORIGIN = 0x9FFFFFC0, LENGTH = 0x00000040
}

SECTIONS
{
  .text : ALIGN(0x8)
  {
    *(.text);
  } > EMI
  .init : ALIGN(0x8)
  {
    *(.init);
  } > EMI
  .fini : ALIGN(0x8)
  {
    *(.fini);
  } > EMI
  .data : ALIGN(0x8)
  {
    *(.data);
  } > C0_IMU0
  .bss : ALIGN(0x8)
  {
    *(.bss);
  } > C0_IMU0
  .stack : ALIGN(0x8)
  {
    *(.stack);
  } > C0_IMU0
  .data_shared_src.bss : ALIGN(0x8)
  {
    *(.data_shared_src.bss);
  } > EMI
  .data_shared_dst.bss : ALIGN(0x8)
  {
    *(.data_shared_dst.bss);
  } > EMI
  .rpc_services.bss : ALIGN(0x8)
  {
    *(.rpc_services.bss);
  } > EMI
  .rpc_services : ALIGN(0x8)
  {
    *(.rpc_services);
  } > EMI
  .text_life : ALIGN(0x8)
  {
    *(.text_life);
  } > EMI
  .data_life : ALIGN(0x8)
  {
    *(.data_life);
  } > C0_IMU3
  .data_hal_syncro : ALIGN(0x8)
  {
    *(.data_hal_syncro);
  } > SYNCRO
  .heap : ALIGN(0x8)
  {
    *(.heap);
	. = ORIGIN(EMI) + LENGTH(EMI);
    __HEAP_0_END = .;
  } > EMI
  .heap1 : ALIGN(0x8)
  {
    *(.heap1);
	. = ORIGIN(C0_IMU1) + LENGTH(C0_IMU1);
    __HEAP_1_END = .;
  } > C0_IMU1
  .heap2 : ALIGN(0x8)
  {
    *(.heap2);
	. = ORIGIN(C0_IMU2) + LENGTH(C0_IMU2);
    __HEAP_2_END = .;
  } > C0_IMU2
  .heap3 : ALIGN(0x8)
  {
    *(.heap3);
	. = ORIGIN(C0_IMU3) + LENGTH(C0_IMU3);
    __HEAP_3_END = .;
  } > C0_IMU3
}