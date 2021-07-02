/******************************************************************************
 *	Copyright (C) 2015	Alejandro Colomar Andrés		      *
 *	SPDX-License-Identifier:	GPL-2.0-only			      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
#include <stdio.h>

#include <alx/curses/curses.h>

#include "estadistica/share.h"
#include "estadistica/menus.h"
#include "estadistica/parse.h"


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/


/******************************************************************************
 ******* enums ****************************************************************
 ******************************************************************************/


/******************************************************************************
 ******* structs / unions *****************************************************
 ******************************************************************************/


/******************************************************************************
 ******* variables ************************************************************
 ******************************************************************************/


/******************************************************************************
 ******* static functions (prototypes) ****************************************
 ******************************************************************************/
static	void	init_all	(int argc, char *argv[]);
static	void	cleanup		(void);


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
int	main	(int argc, char *argv[])
{

	init_all(argc, argv);

	print_share_file(SHARE_COPYRIGHT);

	alx_curses_resume();
	menu_main();
	alx_curses_pause();

	cleanup();

	return	0;
}


/******************************************************************************
 ******* static functions (definitions) ***************************************
 ******************************************************************************/
static	void	init_all	(int argc, char *argv[])
{

	alx_curses_init();
	alx_curses_pause();

	parser(argc, argv);
}

static	void	cleanup		(void)
{

	alx_curses_resume();
	alx_curses_deinit();
}


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/
