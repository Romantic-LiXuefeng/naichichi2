# Generated automatically from Makefile.in by configure.
#

SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .o .a
.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

CC=$(CROSS_COMPILE)gcc

CFLAGS=-g $(FPUHINT)
CPPFLAGS=-Iinclude -Icrypto -Icrypto/aes -Icrypto/asn1 -Icrypto/bf -Icrypto/bio -Icrypto/bn -Icrypto/buffer -Icrypto/camellia -Icrypto/cast -Icrypto/cms -Icrypto/comp -Icrypto/conf -Icrypto/des -Icrypto/dh -Icrypto/dsa -Icrypto/dso -Icrypto/ec -Icrypto/ecdh -Icrypto/ecdsa -Icrypto/engine -Icrypto/err -Icrypto/evp -Icrypto/modes -I. -DLINUX -D_DEBUG -D_CRT_NON_CONFORMING_SWPRINTFS -DOPENSSL_THREADS -DL_ENDIAN  -D_CRT_SECURE_NO_DEPRECATE -DOPENSSL_NO_ASM -DOPENSSL_NO_GMP -DOPENSSL_NO_JPAKE -DOPENSSL_NO_KRB5 -DOPENSSL_NO_MD2 -DOPENSSL_NO_RFC3779 -DOPENSSL_NO_STORE -DOPENSSL_NO_STATIC_ENGINE -DOPENSSL_BUILD_SHLIBCRYPTO -DMK1MF_BUILD -D_LIB $(FPUHINT)
# LDFLAGS= 
RM=/bin/rm -f
AR=/usr$(CROSS_COMPILE)ar r
RANLIB=$(CROSS_COMPILE)ranlib
TARGET=openssl.a

## install
prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
libdir=${exec_prefix}/lib
includedir=${prefix}/include
INSTALL=/usr/bin/install -c
INSTALL_DATA=${INSTALL} -m 644
INSTALL_PROGRAM=${INSTALL}

## rules
OBJ = \
./crypto/evp/evp_fips.o \
./crypto/evp/e_aes.o \
./crypto/evp/e_aes_cbc_hmac_sha1.o \
./crypto/modes/cbc128.o \
./crypto/modes/ccm128.o \
./crypto/modes/cfb128.o \
./crypto/modes/ctr128.o \
./crypto/modes/gcm128.o \
./crypto/modes/ofb128.o \
./crypto/modes/xts128.o \
./crypto/srp/srp_lib.o \
./crypto/srp/srp_vfy.o \
./ssl/bio_ssl.o \
./ssl/d1_both.o \
./ssl/d1_clnt.o \
./ssl/d1_enc.o \
./ssl/d1_lib.o \
./ssl/d1_meth.o \
./ssl/d1_pkt.o \
./ssl/d1_srtp.o \
./ssl/d1_srvr.o \
./ssl/kssl.o \
./ssl/s23_clnt.o \
./ssl/s23_lib.o \
./ssl/s23_meth.o \
./ssl/s23_pkt.o \
./ssl/s23_srvr.o \
./ssl/s2_clnt.o \
./ssl/s2_enc.o \
./ssl/s2_lib.o \
./ssl/s2_meth.o \
./ssl/s2_pkt.o \
./ssl/s2_srvr.o \
./ssl/s3_both.o \
./ssl/s3_clnt.o \
./ssl/s3_enc.o \
./ssl/s3_lib.o \
./ssl/s3_meth.o \
./ssl/s3_pkt.o \
./ssl/s3_srvr.o \
./ssl/ssl_algs.o \
./ssl/ssl_asn1.o \
./ssl/ssl_cert.o \
./ssl/ssl_ciph.o \
./ssl/ssl_err.o \
./ssl/ssl_err2.o \
./ssl/ssl_lib.o \
./ssl/ssl_rsa.o \
./ssl/ssl_sess.o \
./ssl/ssl_stat.o \
./ssl/ssl_txt.o \
./ssl/t1_clnt.o \
./ssl/t1_enc.o \
./ssl/t1_lib.o \
./ssl/t1_meth.o \
./ssl/t1_reneg.o \
./ssl/t1_srvr.o \
./ssl/tls_srp.o \
./crypto/buffer/buf_str.o \
./crypto/camellia/cmll_utl.o \
./crypto/cmac/cmac.o \
./crypto/cmac/cm_ameth.o \
./crypto/cmac/cm_pmeth.o \
./crypto/cms/cms_pwri.o \
./crypto/cpt_err.o \
./crypto/cryptlib.o \
./crypto/cversion.o \
./crypto/ec/ec2_oct.o \
./crypto/ec/ecp_oct.o \
./crypto/ec/ec_oct.o \
./crypto/engine/eng_rdrand.o \
./crypto/engine/eng_rsax.o \
./crypto/evp/e_aes_cbc_hmac_sha1.o \
./crypto/evp/e_rc4_hmac_md5.o \
./crypto/ex_data.o \
./crypto/mem.o \
./crypto/mem_clr.o \
./crypto/mem_dbg.o \
./crypto/modes/ccm128.o \
./crypto/modes/gcm128.o \
./crypto/modes/xts128.o \
./crypto/o_dir.o \
./crypto/o_init.o \
./crypto/o_time.o \
./crypto/rc4/rc4_utl.o \
./crypto/rsa/rsa_crpt.o \
./crypto/uid.o \
./crypto/rc2/rc2_cbc.o \
./crypto/rc2/rc2_ecb.o \
./crypto/rc2/rc2_skey.o \
./crypto/rc2/rc2cfb64.o \
./crypto/rc2/rc2ofb64.o \
./crypto/rc4/rc4_enc.o \
./crypto/rc4/rc4_skey.o \
./crypto/idea/i_cbc.o \
./crypto/idea/i_cfb64.o \
./crypto/idea/i_ecb.o \
./crypto/idea/i_ofb64.o \
./crypto/idea/i_skey.o \
./crypto/bf/bf_cfb64.o \
./crypto/bf/bf_ecb.o \
./crypto/bf/bf_enc.o \
./crypto/bf/bf_ofb64.o \
./crypto/bf/bf_skey.o \
./crypto/cast/c_cfb64.o \
./crypto/cast/c_ecb.o \
./crypto/cast/c_enc.o \
./crypto/cast/c_ofb64.o \
./crypto/cast/c_skey.o \
./crypto/ripemd/rmd_dgst.o \
./crypto/ripemd/rmd_one.o \
./crypto/des/cbc_cksm.o \
./crypto/des/cbc_enc.o \
./crypto/des/cfb64ede.o \
./crypto/des/cfb64enc.o \
./crypto/des/cfb_enc.o \
./crypto/des/des_enc.o \
./crypto/des/des_old.o \
./crypto/des/des_old2.o \
./crypto/des/ecb3_enc.o \
./crypto/des/ecb_enc.o \
./crypto/des/ede_cbcm_enc.o \
./crypto/des/enc_read.o \
./crypto/des/enc_writ.o \
./crypto/des/fcrypt.o \
./crypto/des/fcrypt_b.o \
./crypto/des/ofb64ede.o \
./crypto/des/ofb64enc.o \
./crypto/des/ofb_enc.o \
./crypto/des/pcbc_enc.o \
./crypto/des/qud_cksm.o \
./crypto/des/rand_key.o \
./crypto/des/read2pwd.o \
./crypto/des/rpc_enc.o \
./crypto/des/set_key.o \
./crypto/des/str2key.o \
./crypto/des/xcbc_enc.o \
./crypto/aes/aes_cbc.o \
./crypto/aes/aes_cfb.o \
./crypto/aes/aes_core.o \
./crypto/aes/aes_ctr.o \
./crypto/aes/aes_ecb.o \
./crypto/aes/aes_ige.o \
./crypto/aes/aes_misc.o \
./crypto/aes/aes_ofb.o \
./crypto/aes/aes_wrap.o \
./crypto/camellia/camellia.o \
./crypto/camellia/cmll_cbc.o \
./crypto/camellia/cmll_cfb.o \
./crypto/camellia/cmll_ctr.o \
./crypto/camellia/cmll_ecb.o \
./crypto/camellia/cmll_misc.o \
./crypto/camellia/cmll_ofb.o \
./crypto/seed/seed.o \
./crypto/seed/seed_cbc.o \
./crypto/seed/seed_cfb.o \
./crypto/seed/seed_ecb.o \
./crypto/seed/seed_ofb.o \
./crypto/modes/cbc128.o \
./crypto/modes/cfb128.o \
./crypto/modes/ctr128.o \
./crypto/modes/cts128.o \
./crypto/modes/ofb128.o \
./crypto/bn/bn_add.o \
./crypto/bn/bn_asm.o \
./crypto/bn/bn_blind.o \
./crypto/bn/bn_const.o \
./crypto/bn/bn_ctx.o \
./crypto/bn/bn_depr.o \
./crypto/bn/bn_div.o \
./crypto/bn/bn_err.o \
./crypto/bn/bn_exp.o \
./crypto/bn/bn_exp2.o \
./crypto/bn/bn_gcd.o \
./crypto/bn/bn_gf2m.o \
./crypto/bn/bn_kron.o \
./crypto/bn/bn_lib.o \
./crypto/bn/bn_mod.o \
./crypto/bn/bn_mont.o \
./crypto/bn/bn_mpi.o \
./crypto/bn/bn_mul.o \
./crypto/bn/bn_nist.o \
./crypto/bn/bn_prime.o \
./crypto/bn/bn_print.o \
./crypto/bn/bn_rand.o \
./crypto/bn/bn_recp.o \
./crypto/bn/bn_shift.o \
./crypto/bn/bn_sqr.o \
./crypto/bn/bn_sqrt.o \
./crypto/bn/bn_word.o \
./crypto/rsa/rsa_ameth.o \
./crypto/rsa/rsa_asn1.o \
./crypto/rsa/rsa_chk.o \
./crypto/rsa/rsa_depr.o \
./crypto/rsa/rsa_eay.o \
./crypto/rsa/rsa_err.o \
./crypto/rsa/rsa_gen.o \
./crypto/rsa/rsa_lib.o \
./crypto/rsa/rsa_none.o \
./crypto/rsa/rsa_null.o \
./crypto/rsa/rsa_oaep.o \
./crypto/rsa/rsa_pk1.o \
./crypto/rsa/rsa_pmeth.o \
./crypto/rsa/rsa_prn.o \
./crypto/rsa/rsa_pss.o \
./crypto/rsa/rsa_saos.o \
./crypto/rsa/rsa_sign.o \
./crypto/rsa/rsa_ssl.o \
./crypto/rsa/rsa_x931.o \
./crypto/dsa/dsa_ameth.o \
./crypto/dsa/dsa_asn1.o \
./crypto/dsa/dsa_depr.o \
./crypto/dsa/dsa_err.o \
./crypto/dsa/dsa_gen.o \
./crypto/dsa/dsa_key.o \
./crypto/dsa/dsa_lib.o \
./crypto/dsa/dsa_ossl.o \
./crypto/dsa/dsa_pmeth.o \
./crypto/dsa/dsa_prn.o \
./crypto/dsa/dsa_sign.o \
./crypto/dsa/dsa_vrf.o \
./crypto/rand/md_rand.o \
./crypto/rand/rand_egd.o \
./crypto/rand/rand_err.o \
./crypto/rand/rand_lib.o \
./crypto/rand/rand_nw.o \
./crypto/rand/rand_os2.o \
./crypto/rand/rand_unix.o \
./crypto/rand/rand_win.o \
./crypto/rand/randfile.o \
./crypto/bio/b_dump.o \
./crypto/bio/b_print.o \
./crypto/bio/b_sock.o \
./crypto/bio/bf_buff.o \
./crypto/bio/bf_nbio.o \
./crypto/bio/bf_null.o \
./crypto/bio/bio_cb.o \
./crypto/bio/bio_err.o \
./crypto/bio/bio_lib.o \
./crypto/bio/bss_acpt.o \
./crypto/bio/bss_bio.o \
./crypto/bio/bss_conn.o \
./crypto/bio/bss_dgram.o \
./crypto/bio/bss_fd.o \
./crypto/bio/bss_file.o \
./crypto/bio/bss_log.o \
./crypto/bio/bss_mem.o \
./crypto/bio/bss_null.o \
./crypto/bio/bss_sock.o \
./crypto/err/err.o \
./crypto/err/err_all.o \
./crypto/err/err_prn.o \
./crypto/ui/ui_compat.o \
./crypto/ui/ui_err.o \
./crypto/ui/ui_lib.o \
./crypto/ui/ui_openssl.o \
./crypto/ui/ui_util.o \
./crypto/x509/by_dir.o \
./crypto/x509/by_file.o \
./crypto/x509/x509_att.o \
./crypto/x509/x509_cmp.o \
./crypto/x509/x509_d2.o \
./crypto/x509/x509_def.o \
./crypto/x509/x509_err.o \
./crypto/x509/x509_ext.o \
./crypto/x509/x509_lu.o \
./crypto/x509/x509_obj.o \
./crypto/x509/x509_r2x.o \
./crypto/x509/x509_req.o \
./crypto/x509/x509_set.o \
./crypto/x509/x509_trs.o \
./crypto/x509/x509_txt.o \
./crypto/x509/x509_v3.o \
./crypto/x509/x509_vfy.o \
./crypto/x509/x509_vpm.o \
./crypto/x509/x509cset.o \
./crypto/x509/x509name.o \
./crypto/x509/x509rset.o \
./crypto/x509/x509spki.o \
./crypto/x509/x509type.o \
./crypto/x509/x_all.o \
./crypto/asn1/a_bitstr.o \
./crypto/asn1/a_bool.o \
./crypto/asn1/a_bytes.o \
./crypto/asn1/a_d2i_fp.o \
./crypto/asn1/a_digest.o \
./crypto/asn1/a_dup.o \
./crypto/asn1/a_enum.o \
./crypto/asn1/a_gentm.o \
./crypto/asn1/a_i2d_fp.o \
./crypto/asn1/a_int.o \
./crypto/asn1/a_mbstr.o \
./crypto/asn1/a_object.o \
./crypto/asn1/a_octet.o \
./crypto/asn1/a_print.o \
./crypto/asn1/a_set.o \
./crypto/asn1/a_sign.o \
./crypto/asn1/a_strex.o \
./crypto/asn1/a_strnid.o \
./crypto/asn1/a_time.o \
./crypto/asn1/a_type.o \
./crypto/asn1/a_utctm.o \
./crypto/asn1/a_utf8.o \
./crypto/asn1/a_verify.o \
./crypto/asn1/ameth_lib.o \
./crypto/asn1/asn1_err.o \
./crypto/asn1/asn1_gen.o \
./crypto/asn1/asn1_lib.o \
./crypto/asn1/asn1_par.o \
./crypto/asn1/asn_mime.o \
./crypto/asn1/asn_moid.o \
./crypto/asn1/asn_pack.o \
./crypto/asn1/bio_asn1.o \
./crypto/asn1/bio_ndef.o \
./crypto/asn1/d2i_pr.o \
./crypto/asn1/d2i_pu.o \
./crypto/asn1/evp_asn1.o \
./crypto/asn1/f_enum.o \
./crypto/asn1/f_int.o \
./crypto/asn1/f_string.o \
./crypto/asn1/i2d_pr.o \
./crypto/asn1/i2d_pu.o \
./crypto/asn1/n_pkey.o \
./crypto/asn1/nsseq.o \
./crypto/asn1/p5_pbe.o \
./crypto/asn1/p5_pbev2.o \
./crypto/asn1/p8_pkey.o \
./crypto/asn1/t_bitst.o \
./crypto/asn1/t_crl.o \
./crypto/asn1/t_pkey.o \
./crypto/asn1/t_req.o \
./crypto/asn1/t_spki.o \
./crypto/asn1/t_x509.o \
./crypto/asn1/t_x509a.o \
./crypto/asn1/tasn_dec.o \
./crypto/asn1/tasn_enc.o \
./crypto/asn1/tasn_fre.o \
./crypto/asn1/tasn_new.o \
./crypto/asn1/tasn_prn.o \
./crypto/asn1/tasn_typ.o \
./crypto/asn1/tasn_utl.o \
./crypto/asn1/x_algor.o \
./crypto/asn1/x_attrib.o \
./crypto/asn1/x_bignum.o \
./crypto/asn1/x_crl.o \
./crypto/asn1/x_exten.o \
./crypto/asn1/x_info.o \
./crypto/asn1/x_long.o \
./crypto/asn1/x_name.o \
./crypto/asn1/x_nx509.o \
./crypto/asn1/x_pkey.o \
./crypto/asn1/x_pubkey.o \
./crypto/asn1/x_req.o \
./crypto/asn1/x_sig.o \
./crypto/asn1/x_spki.o \
./crypto/asn1/x_val.o \
./crypto/asn1/x_x509.o \
./crypto/asn1/x_x509a.o \
./crypto/objects/o_names.o \
./crypto/objects/obj_dat.o \
./crypto/objects/obj_err.o \
./crypto/objects/obj_lib.o \
./crypto/objects/obj_xref.o \
./crypto/evp/bio_b64.o \
./crypto/evp/bio_enc.o \
./crypto/evp/bio_md.o \
./crypto/evp/bio_ok.o \
./crypto/evp/c_all.o \
./crypto/evp/c_allc.o \
./crypto/evp/c_alld.o \
./crypto/evp/digest.o \
./crypto/evp/e_aes.o \
./crypto/evp/e_bf.o \
./crypto/evp/e_camellia.o \
./crypto/evp/e_cast.o \
./crypto/evp/e_des.o \
./crypto/evp/e_des3.o \
./crypto/evp/e_idea.o \
./crypto/evp/e_null.o \
./crypto/evp/e_old.o \
./crypto/evp/e_rc2.o \
./crypto/evp/e_rc4.o \
./crypto/evp/e_rc5.o \
./crypto/evp/e_seed.o \
./crypto/evp/e_xcbc_d.o \
./crypto/evp/encode.o \
./crypto/evp/evp_acnf.o \
./crypto/evp/evp_enc.o \
./crypto/evp/evp_err.o \
./crypto/evp/evp_key.o \
./crypto/evp/evp_lib.o \
./crypto/evp/evp_pbe.o \
./crypto/evp/evp_pkey.o \
./crypto/evp/m_dss.o \
./crypto/evp/m_dss1.o \
./crypto/evp/m_ecdsa.o \
./crypto/evp/m_md2.o \
./crypto/evp/m_md4.o \
./crypto/evp/m_md5.o \
./crypto/evp/m_mdc2.o \
./crypto/evp/m_null.o \
./crypto/evp/m_ripemd.o \
./crypto/evp/m_sha.o \
./crypto/evp/m_sha1.o \
./crypto/evp/m_sigver.o \
./crypto/evp/m_wp.o \
./crypto/evp/names.o \
./crypto/evp/openbsd_hw.o \
./crypto/evp/p5_crpt.o \
./crypto/evp/p5_crpt2.o \
./crypto/evp/p_dec.o \
./crypto/evp/p_enc.o \
./crypto/evp/p_lib.o \
./crypto/evp/p_open.o \
./crypto/evp/p_seal.o \
./crypto/evp/p_sign.o \
./crypto/evp/p_verify.o \
./crypto/evp/pmeth_fn.o \
./crypto/evp/pmeth_gn.o \
./crypto/evp/pmeth_lib.o \
./crypto/buffer/buf_err.o \
./crypto/buffer/buffer.o \
./crypto/cms/cms_asn1.o \
./crypto/cms/cms_att.o \
./crypto/cms/cms_cd.o \
./crypto/cms/cms_dd.o \
./crypto/cms/cms_enc.o \
./crypto/cms/cms_env.o \
./crypto/cms/cms_err.o \
./crypto/cms/cms_ess.o \
./crypto/cms/cms_io.o \
./crypto/cms/cms_lib.o \
./crypto/cms/cms_sd.o \
./crypto/cms/cms_smime.o \
./crypto/engine/eng_all.o \
./crypto/engine/eng_cnf.o \
./crypto/engine/eng_cryptodev.o \
./crypto/engine/eng_ctrl.o \
./crypto/engine/eng_dyn.o \
./crypto/engine/eng_err.o \
./crypto/engine/eng_fat.o \
./crypto/engine/eng_init.o \
./crypto/engine/eng_lib.o \
./crypto/engine/eng_list.o \
./crypto/engine/eng_openssl.o \
./crypto/engine/eng_pkey.o \
./crypto/engine/eng_table.o \
./crypto/engine/tb_asnmth.o \
./crypto/engine/tb_cipher.o \
./crypto/engine/tb_dh.o \
./crypto/engine/tb_digest.o \
./crypto/engine/tb_dsa.o \
./crypto/engine/tb_ecdh.o \
./crypto/engine/tb_ecdsa.o \
./crypto/engine/tb_pkmeth.o \
./crypto/engine/tb_rand.o \
./crypto/engine/tb_rsa.o \
./crypto/engine/tb_store.o \
./crypto/stack/stack.o \
./crypto/pkcs7/bio_pk7.o \
./crypto/pkcs7/pk7_asn1.o \
./crypto/pkcs7/pk7_attr.o \
./crypto/pkcs7/pk7_doit.o \
./crypto/pkcs7/pk7_lib.o \
./crypto/pkcs7/pk7_mime.o \
./crypto/pkcs7/pk7_smime.o \
./crypto/pkcs7/pkcs7err.o \
./crypto/dh/dh_ameth.o \
./crypto/dh/dh_asn1.o \
./crypto/dh/dh_check.o \
./crypto/dh/dh_depr.o \
./crypto/dh/dh_err.o \
./crypto/dh/dh_gen.o \
./crypto/dh/dh_key.o \
./crypto/dh/dh_lib.o \
./crypto/dh/dh_pmeth.o \
./crypto/dh/dh_prn.o \
./crypto/ocsp/ocsp_asn.o \
./crypto/ocsp/ocsp_cl.o \
./crypto/ocsp/ocsp_err.o \
./crypto/ocsp/ocsp_ext.o \
./crypto/ocsp/ocsp_ht.o \
./crypto/ocsp/ocsp_lib.o \
./crypto/ocsp/ocsp_prn.o \
./crypto/ocsp/ocsp_srv.o \
./crypto/ocsp/ocsp_vfy.o \
./crypto/x509v3/pcy_cache.o \
./crypto/x509v3/pcy_data.o \
./crypto/x509v3/pcy_lib.o \
./crypto/x509v3/pcy_map.o \
./crypto/x509v3/pcy_node.o \
./crypto/x509v3/pcy_tree.o \
./crypto/x509v3/v3_addr.o \
./crypto/x509v3/v3_akey.o \
./crypto/x509v3/v3_akeya.o \
./crypto/x509v3/v3_alt.o \
./crypto/x509v3/v3_asid.o \
./crypto/x509v3/v3_bcons.o \
./crypto/x509v3/v3_bitst.o \
./crypto/x509v3/v3_conf.o \
./crypto/x509v3/v3_cpols.o \
./crypto/x509v3/v3_crld.o \
./crypto/x509v3/v3_enum.o \
./crypto/x509v3/v3_extku.o \
./crypto/x509v3/v3_genn.o \
./crypto/x509v3/v3_ia5.o \
./crypto/x509v3/v3_info.o \
./crypto/x509v3/v3_int.o \
./crypto/x509v3/v3_lib.o \
./crypto/x509v3/v3_ncons.o \
./crypto/x509v3/v3_ocsp.o \
./crypto/x509v3/v3_pci.o \
./crypto/x509v3/v3_pcia.o \
./crypto/x509v3/v3_pcons.o \
./crypto/x509v3/v3_pku.o \
./crypto/x509v3/v3_pmaps.o \
./crypto/x509v3/v3_prn.o \
./crypto/x509v3/v3_purp.o \
./crypto/x509v3/v3_skey.o \
./crypto/x509v3/v3_sxnet.o \
./crypto/x509v3/v3_utl.o \
./crypto/x509v3/v3err.o \
./crypto/ts/ts_asn1.o \
./crypto/ts/ts_conf.o \
./crypto/ts/ts_err.o \
./crypto/ts/ts_lib.o \
./crypto/ts/ts_req_print.o \
./crypto/ts/ts_req_utils.o \
./crypto/ts/ts_rsp_print.o \
./crypto/ts/ts_rsp_sign.o \
./crypto/ts/ts_rsp_utils.o \
./crypto/ts/ts_rsp_verify.o \
./crypto/ts/ts_verify_ctx.o \
./crypto/conf/conf_api.o \
./crypto/conf/conf_def.o \
./crypto/conf/conf_err.o \
./crypto/conf/conf_lib.o \
./crypto/conf/conf_mall.o \
./crypto/conf/conf_mod.o \
./crypto/conf/conf_sap.o \
./crypto/ec/ec2_mult.o \
./crypto/ec/ec2_smpl.o \
./crypto/ec/ec_ameth.o \
./crypto/ec/ec_asn1.o \
./crypto/ec/ec_check.o \
./crypto/ec/ec_curve.o \
./crypto/ec/ec_cvt.o \
./crypto/ec/ec_err.o \
./crypto/ec/ec_key.o \
./crypto/ec/ec_lib.o \
./crypto/ec/ec_mult.o \
./crypto/ec/ec_pmeth.o \
./crypto/ec/ec_print.o \
./crypto/ec/eck_prn.o \
./crypto/ec/ecp_mont.o \
./crypto/ec/ecp_nist.o \
./crypto/ec/ecp_smpl.o \
./crypto/ecdh/ech_err.o \
./crypto/ecdh/ech_key.o \
./crypto/ecdh/ech_lib.o \
./crypto/ecdh/ech_ossl.o \
./crypto/ecdsa/ecs_asn1.o \
./crypto/ecdsa/ecs_err.o \
./crypto/ecdsa/ecs_lib.o \
./crypto/ecdsa/ecs_ossl.o \
./crypto/ecdsa/ecs_sign.o \
./crypto/ecdsa/ecs_vrf.o \
./crypto/md5/md5_dgst.o \
./crypto/md5/md5_one.o \
./crypto/md4/md4_dgst.o \
./crypto/md4/md4_one.o \
./crypto/lhash/lh_stats.o \
./crypto/lhash/lhash.o \
./crypto/dso/dso_beos.o \
./crypto/dso/dso_dl.o \
./crypto/dso/dso_dlfcn.o \
./crypto/dso/dso_err.o \
./crypto/dso/dso_lib.o \
./crypto/dso/dso_null.o \
./crypto/dso/dso_openssl.o \
./crypto/dso/dso_vms.o \
./crypto/dso/dso_win32.o \
./crypto/pkcs12/p12_add.o \
./crypto/pkcs12/p12_asn.o \
./crypto/pkcs12/p12_attr.o \
./crypto/pkcs12/p12_crpt.o \
./crypto/pkcs12/p12_crt.o \
./crypto/pkcs12/p12_decr.o \
./crypto/pkcs12/p12_init.o \
./crypto/pkcs12/p12_key.o \
./crypto/pkcs12/p12_kiss.o \
./crypto/pkcs12/p12_mutl.o \
./crypto/pkcs12/p12_npas.o \
./crypto/pkcs12/p12_p8d.o \
./crypto/pkcs12/p12_p8e.o \
./crypto/pkcs12/p12_utl.o \
./crypto/pkcs12/pk12err.o \
./crypto/hmac/hm_ameth.o \
./crypto/hmac/hm_pmeth.o \
./crypto/hmac/hmac.o \
./crypto/sha/sha1_one.o \
./crypto/sha/sha1dgst.o \
./crypto/sha/sha256.o \
./crypto/sha/sha512.o \
./crypto/sha/sha512t.o \
./crypto/sha/sha_dgst.o \
./crypto/sha/sha_one.o \
./crypto/comp/c_rle.o \
./crypto/comp/c_zlib.o \
./crypto/comp/comp_err.o \
./crypto/comp/comp_lib.o \
./crypto/pem/pem_all.o \
./crypto/pem/pem_err.o \
./crypto/pem/pem_info.o \
./crypto/pem/pem_lib.o \
./crypto/pem/pem_oth.o \
./crypto/pem/pem_pk8.o \
./crypto/pem/pem_pkey.o \
./crypto/pem/pem_seal.o \
./crypto/pem/pem_sign.o \
./crypto/pem/pem_x509.o \
./crypto/pem/pem_xaux.o \
./crypto/pem/pvkfmt.o \
./crypto/whrlpool/wp_block.o \
./crypto/whrlpool/wp_dgst.o \
./crypto/mdc2/mdc2_one.o \
./crypto/mdc2/mdc2dgst.o \
./crypto/krb5/krb5_asn.o \
./crypto/txt_db/txt_db.o \
./crypto/pqueue/pqueue.o \
./crypto/evp/e_aes_cbc_hmac_sha1.o \
./crypto/modes/ccm128.o \
./crypto/modes/gcm128.o \
./crypto/modes/xts128.o \
./crypto/modes/cbc128.o \
./crypto/modes/cfb128.o \
./crypto/modes/ctr128.o \
./crypto/modes/ofb128.o \
./crypto/evp/e_aes.o 

############################################################

all: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) $@ $?
	$(RANLIB) $@

############################################################

install: install.lib install.include install.bin

install.lib: $(TARGET)
	${INSTALL} -d ${libdir}
	${INSTALL_DATA} $(TARGET) ${libdir}

install.include:
	${INSTALL} -d ${includedir}/sent
	${INSTALL_DATA} include/sent/*.h ${includedir}/sent

install.bin: libsent-config-dist
	${INSTALL} -d ${bindir}
	${INSTALL_PROGRAM} libsent-config-dist ${bindir}/libsent-config

clean:
	$(RM) *~ src/*/*~ src/*/*.o src/*/*/*.o src/*/*/*/*.o src/*/*/*/*/*.o include/sent/*~ *.a
	$(RM) config.log config.cache

distclean:
	$(RM) *~ *.o */*.o */*/*.o
	$(RM) config.log config.cache
	$(RM) libsent-config libsent-config-dist
	$(RM) config.status include/sent/config.h
	$(RM) $(TARGET)
	$(RM) Makefile
