require_vector_novtype(false, false);
float old_vflmul = P.VU.vflmul;
int new_vlmul = int8_t(extract64(RS2, 0, 3) << 5) >> 5;
float new_vflmul = new_vlmul >= 0 ? 1 << new_vlmul : 1.0 / (1 << -new_vlmul);

if (!P.VU.phyreg_sorting &&
    old_vflmul != new_vflmul &&
    (new_vflmul > 1.0) &&
    (old_vflmul < new_vflmul)) {
  printf("old vflmul = %f, new vflmul = %f\n", old_vflmul, new_vflmul);
  P.VU.set_vl(insn.rd(), insn.rs1(), RS1, P.VU.vtype);
  P.VU.phyreg_sorting = true;
 throw trap_lmul_change(insn.bits());
} else {
  P.VU.phyreg_sorting = false;
  WRITE_RD(P.VU.set_vl(insn.rd(), insn.rs1(), RS1, RS2));
}
