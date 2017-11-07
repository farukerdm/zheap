/*-------------------------------------------------------------------------
 *
 * undoactiondesc.c
 *	  rmgr descriptor routines for access/undo/undoactionxlog.c
 *
 * Portions Copyright (c) 1996-2017, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/backend/access/rmgrdesc/undoactiondesc.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "access/undoaction_xlog.h"

void
undoaction_desc(StringInfo buf, XLogReaderState *record)
{
	char	   *rec = XLogRecGetData(record);
	uint8		info = XLogRecGetInfo(record) & ~XLR_INFO_MASK;

	if (info == XLOG_UNDO_INSERT)
	{
		xl_undo_insert *xlrec = (xl_undo_insert *) rec;

		appendStringInfo(buf, "off %u", xlrec->offnum);
	}
}

const char *
undoaction_identify(uint8 info)
{
	const char *id = NULL;

	switch (info & ~XLR_INFO_MASK)
	{
		case XLOG_UNDO_INSERT:
			id = "UNDO INSERT";
			break;
	}

	return id;
}