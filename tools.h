#if (!(defined(eoC_TOOLS_defined)))
#define eoC_TOOLS_defined 
#if ((defined(__STDC_VERSION__))&&(((__STDC_VERSION__)>=(201112L))))
#define eoC_TOOLS_error(x) _Static_assert(0,x)
#elif ((defined(__cplusplus))&&(((__cplusplus)>=(201103L))))
#define eoC_TOOLS_error(x) static_assert(0,x)
#else
#define eoC_TOOLS_error(x) {{{!!!ERROR x ERROR!!!}}}
#endif
#define eoC_TOOLS_expand(x) x
#define eoC_TOOLS_countHELPER0(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_a,_b,_c,_d,_e,_f,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_1a,_1b,_1c,_1d,_1e,_1f,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_2a,_2b,_2c,_2d,_2e,_2f,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_3a,_3b,_3c,_3d,_3e,_3f,_40,x) x
#endif
