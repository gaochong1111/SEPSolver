(set-logic QF_SHID)

(declare-sort RefDll_t 0)


(declare-datatypes (
	(Dll_t 0)
	) (
	((c_Dll_t (next RefDll_t) (prev RefDll_t) ))
	)
)


(declare-heap (RefDll_t Dll_t) 
)

(define-fun-rec dll ((fr RefDll_t)(bk RefDll_t)(pr RefDll_t)(nx RefDll_t)) Bool
	(or 
		(and 
			(= fr nx)
			(= bk pr)
		)

		(exists ((u RefDll_t))
	 
		(and 
			(distinct fr nx)
			(distinct bk pr)
		(sep 
			(pto fr (c_Dll_t u pr ))
			(dll u bk fr nx )
		)

		)

		)

	)
)


(declare-const x_emp RefDll_t)
(declare-const w_emp RefDll_t)
(declare-const y_emp RefDll_t)
(declare-const z_emp RefDll_t)

(assert 
		(and 
			(distinct x_emp z_emp)
			(distinct y_emp z_emp)
			(distinct w_emp z_emp)
		(sep 
			(pto x_emp (c_Dll_t w_emp z_emp ))
			(pto w_emp (c_Dll_t y_emp x_emp ))
			(pto y_emp (c_Dll_t z_emp w_emp ))
		)

		)

)

(assert (not 
			(dll x_emp y_emp z_emp z_emp )
))

(check-sat)

(_ emp RefDll_t Dll_t)