{
    'targets': [
        {
            'target_name': 'lp_solve',
            'dependencies': [
                '<(module_root_dir)/deps/lp_solve/binding.gyp:lp_solve_5.5'
            ],
            'defines': [
            ],
            'include_dirs': [
               "<!(node -e \"require('nan')\")"
            ],
            'sources': [
                'lp_solve.cc', 
            ],
        }
    ]
}