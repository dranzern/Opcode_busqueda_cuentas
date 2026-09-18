/*******************************************************************
 *
 *	Copyright (c) 2023 Totalplay
 *
 * 	Nombre: fm_totalplay_busqueda_cuentas.c
 * 	Opcode: TPL_OP_BUSQUEDA_CUENTAS
 * 	Numero: 25015
 *
 *******************************************************************/

#include "pcm.h"
#include "cm_fm.h"
#include "pin_errs.h"
#include "pinlog.h"
#include "tpl_ops.h"
#include "tpl_flds.h"
#include "ops/ar.h"
#include "ops/bal.h"
#include "ops/bill.h"
#include "pin_bill.h"

#include <time.h>
#include <string.h>

#define FILE_SOURCE_ID "fm_totalplay_busqueda_cuentas"
#define FILE_VERSION_ID 2024020201



/********************************************************************/
	
			/*	ENTRADA
			r << EOF 1
			0 PIN_FLD_POID POID [0] 0.0.0.1 /account 1
			0 PIN_FLD_ACCOUNT_NO        STR [0] ""
			EOF
			xop TPL_OP_BUSQUEDA_CUENTAS 0 1			

/********************************************************************/

EXPORT_OP void 
op_tpl_busqueda_cuentas(
	cm_nap_connection_t *connp,
	u_int               opcode,
	u_int               flags,
	pin_flist_t         *i_flistp,
	pin_flist_t         **o_flistpp,
	pin_errbuf_t        *ebufp);

static void
fm_totalplay_busqueda_cuentas(
	pcm_context_t       *ctxp,
	u_int               flags,
	pin_flist_t         *i_flistp,
	pin_flist_t         **o_flistpp,
	pin_errbuf_t        *ebufp);
	
/********************************************************************/	

void 
op_tpl_busqueda_cuentas(
	cm_nap_connection_t	*connp,
	u_int			opcode,
	u_int			flags,
	pin_flist_t		*i_flistp,
	pin_flist_t		**o_flistpp,
	pin_errbuf_t		*ebufp)
{
	pcm_context_t		*ctxp = connp->dm_ctx;
	pin_flist_t		*r_flistp = NULL;

	/***********************************************************
	* Null out results until we have some.
	***********************************************************/
	*o_flistpp = NULL;
	PIN_ERR_CLEAR_ERR(ebufp);

	/***********************************************************
	* Error out in case opcode is not TPL_OP_BUSQUEDA_CUENTAS
	***********************************************************/
	if (opcode != TPL_OP_BUSQUEDA_CUENTAS) {
		pin_set_err(ebufp, PIN_ERRLOC_FM,
			PIN_ERRCLASS_SYSTEM_DETERMINATE,
			PIN_ERR_BAD_OPCODE, 0, 0, opcode);
			PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"bad opcode in op_tpl_busqueda_cuentas", ebufp);
		return;
	}

	/***********************************************************
	* Debug what we got.
	***********************************************************/
	PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
		"op_tpl_busqueda_cuentas input flist", i_flistp);


	/***********************************************************
	 * Call main function to do it
	 ***********************************************************/
	fm_totalplay_busqueda_cuentas(ctxp, i_flistp, &r_flistp, ebufp);

	/***********************************************************
	 * Results.
	 ***********************************************************/
	if (PIN_ERR_IS_ERR(ebufp)) {
		*o_flistpp = (pin_flist_t *)NULL;
		PIN_FLIST_DESTROY(r_flistp, NULL);
		PIN_ERR_LOG_EBUF(PIN_ERR_LEVEL_ERROR,
			"op_tpl_busqueda_cuentas error", ebufp);
	} else {
		*o_flistpp = r_flistp;
		PIN_ERR_CLEAR_ERR(ebufp);
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG,
			"op_tpl_busqueda_cuentas return flist", r_flistp);
	}

	PIN_ERR_LOG_MSG(PIN_ERR_LEVEL_DEBUG, "finalizo op_tpl_busqueda_cuentas");
	return;
}






static void
fm_totalplay_busqueda_cuentas(
	pcm_context_t       *ctxp,
	pin_flist_t         *i_flistp,
	pin_flist_t         **o_flistpp,
	pin_errbuf_t        *ebufp)
	
	{
	pin_flist_t			*s_flist_p;
	pin_flist_t			*arg_flistp;
	pin_flist_t			*r_flistp;
	pin_flist_t			*final_flistp;
	int32				 s_flags = 256;	
	
		if (PIN_ERR_IS_ERR(ebufp))
		return;
		PIN_ERR_CLEAR_ERR(ebufp);
		
		
		final_flistp = PIN_FLIST_CREATE(ebufp);
		PIN_FLIST_FLD_COPY(i_flistp, PIN_FLD_POID, final_flistp, PIN_FLD_POID,  ebufp);
		
		
		/***********************************************************
		* search flist
		***********************************************************
	
			0 PIN_FLD_POID           POID [0] 0.0.0.1 /search -1 0
			0 PIN_FLD_FLAGS           INT [0] 256
			0 PIN_FLD_TEMPLATE        STR [0] "select X from /account where F1 = V1 "
			0 PIN_FLD_ARGS          ARRAY [1]
				1 PIN_FLD_ACCOUNT_NO   STR [0] ""
			0 PIN_FLD_RESULTS       ARRAY [*] allocated 20, used 0 
			
		***********************************************************/
		
		s_flistp = PIN_FLIST_CREATE(ebufp);
		PIN_FLIST_FLD_PUT(s_flistp, PIN_FLD_POID, PIN_POID_CREATE (1, "/search", -1, ebufp), ebufp);
		PIN_FLIST_FLD_SET(s_flistp, PIN_FLD_FLAGS, &s_flags, ebufp);
		PIN_FLIST_FLD_SET(s_flistp, PIN_FLD_TEMPLATE,"select X from /account where F1 = V1 ", ebufp);
		
		arg_flistp = PIN_FLIST_ELEM_ADD (s_flistp, PIN_FLD_ARGS, 1, ebufp);
		PIN_FLIST_FLD_COPY(i_flistp, PIN_FLD_ACCOUNT_NO, arg_flistp, PIN_FLD_ACCOUNT_NO,  ebufp);
		
		r_flistp = PIN_FLIST_ELEM_ADD (s_flist_p, PIN_FLD_RESULTS, 0, ebufp)
		
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_totalplay_busqueda_cuentas: search input flist", s_flistp);
		PCM_OP(ctxp, PCM_OP_SEARCH, 0, s_flistp, &r_flistp, ebufp);
		PIN_ERR_LOG_FLIST(PIN_ERR_LEVEL_DEBUG, "fm_totalplay_busqueda_cuentas: search out flist", r_flistp);
		
		if (PIN_FLIST_ELEM_COUNT(r_flistp, PIN_FLD_RESULTS, ebufp) > 0) {
			PIN_FLIST_FLD_SET(final_flistp, PIN_FLD_DESCR,"Cuenta Existe ", ebufp);
		}else {
			PIN_FLIST_FLD_SET(final_flistp, PIN_FLD_DESCR,"Cuenta No Existe ", ebufp);
		}
		
		*o_flistpp = PIN_FLIST_COPY( final_flistp ,ebufp);
		
		PIN_FLIST_DESTROY_EX(&s_flist_p, NULL);
		PIN_FLIST_DESTROY_EX(&final_flistp, NULL);
		PIN_FLIST_DESTROY_EX(&r_flistp, NULL);
		
		return;
	}
	
	