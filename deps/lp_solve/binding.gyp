{
    'targets': [
        {
            'target_name': 'lp_solve_5.5',
            'type': 'static_library',
            'defines': [
                'YY_NEVER_INTERACTIVE',
                'PARSER_LP',
                'INVERSE_ACTIVE=INVERSE_LUSOL',
                'RoleIsExternalInvEngine'
            ],
            'include_dirs': [
                'lp_solve_5.5', 
                'lp_solve_5.5/shared',
                'lp_solve_5.5/bfp',
                'lp_solve_5.5/bfp/bfp_LUSOL',
                'lp_solve_5.5/bfp/bfp_LUSOL/LUSOL',
                'lp_solve_5.5/colamd'
            ],
            'sources': [
                'lp_solve_5.5/lp_MDO.c',
                'lp_solve_5.5/shared/commonlib.c',
                'lp_solve_5.5/shared/mmio.c',
                'lp_solve_5.5/shared/myblas.c',
                'lp_solve_5.5/ini.c',
                'lp_solve_5.5/fortify.c',
                'lp_solve_5.5/colamd/colamd.c',
                'lp_solve_5.5/lp_rlp.c',
                'lp_solve_5.5/lp_crash.c',
                'lp_solve_5.5/bfp/bfp_LUSOL/lp_LUSOL.c',
                'lp_solve_5.5/bfp/bfp_LUSOL/LUSOL/lusol.c',
                'lp_solve_5.5/lp_Hash.c',
                'lp_solve_5.5/lp_lib.c',
                'lp_solve_5.5/lp_wlp.c',
                'lp_solve_5.5/lp_matrix.c',
                'lp_solve_5.5/lp_mipbb.c',
                'lp_solve_5.5/lp_MPS.c',
                'lp_solve_5.5/lp_params.c',
                'lp_solve_5.5/lp_presolve.c',
                'lp_solve_5.5/lp_price.c',
                'lp_solve_5.5/lp_pricePSE.c',
                'lp_solve_5.5/lp_report.c',
                'lp_solve_5.5/lp_scale.c',
                'lp_solve_5.5/lp_simplex.c',
                'lp_solve_5.5/lp_SOS.c',
                'lp_solve_5.5/lp_utils.c',
                'lp_solve_5.5/yacc_read.c'
            ],
            'direct_dependent_settings': {
                'include_dirs': ['lp_solve_5.5']
            },
        }
    ]
}
