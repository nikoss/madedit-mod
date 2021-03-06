/*
 * This file is part of the Code::Blocks IDE and licensed under the GNU General Public License, version 3
 * http://www.gnu.org/licenses/gpl-3.0.html
 *
 * $Revision: 10188 $
 * $Id: formattersettings.cpp 10188 2015-04-06 11:50:06Z mortenmacfly $
 * $HeadURL: file:///svn/p/codeblocks/code/trunk/src/plugins/astyle/formattersettings.cpp $
 */

//#include <sdk.h>
#include "formattersettings.h"
#include "astylepredefinedstyles.h"
//#include <configmanager.h>
#include <wx/wx.h>
#include <wx/confbase.h>

FormatterSettings::FormatterSettings()
{
  //ctor
}

FormatterSettings::~FormatterSettings()
{
  //dtor
}

void FormatterSettings::ApplyTo(astyle::ASFormatter& formatter)
{
  // NOTE: Keep this in sync with DlgFormatterSettings::ApplyTo
  wxConfigBase	  *cfg=wxConfigBase::Get(false);
  wxString oldpath=cfg->GetPath();
  cfg->SetPath(wxT("/astyle"));
  //ConfigManager* cfg = Manager::Get()->GetConfigManager(wxT("astyle"));

  long style = cfg->ReadLong(wxT("style"), aspsAllman);
  switch (style)
  {
    case aspsAllman: // Allman (ANSI)
      formatter.setFormattingStyle(astyle::STYLE_ALLMAN);
      break;

    case aspsJava: // Java
      formatter.setFormattingStyle(astyle::STYLE_JAVA);
      break;

    case aspsKr: // K&R
      formatter.setFormattingStyle(astyle::STYLE_KR);
      break;

    case aspsStroustrup: // Stroustrup
      formatter.setFormattingStyle(astyle::STYLE_STROUSTRUP);
      break;

    case aspsWhitesmith: // Whitesmith
      formatter.setFormattingStyle(astyle::STYLE_WHITESMITH);
      break;

    case aspsVTK: // VTK
      formatter.setFormattingStyle(astyle::STYLE_VTK);
      break;

    case aspsBanner: // Banner
      formatter.setFormattingStyle(astyle::STYLE_BANNER);
      break;

    case aspsGnu: // GNU
      formatter.setFormattingStyle(astyle::STYLE_GNU);
      break;

    case aspsLinux: // Linux
      formatter.setFormattingStyle(astyle::STYLE_LINUX);
      break;

    case aspsHorstmann: // Horstmann
      formatter.setFormattingStyle(astyle::STYLE_HORSTMANN);
      break;

    case asps1TBS: // 1TBS
      formatter.setFormattingStyle(astyle::STYLE_1TBS);
      break;

    case aspsGoogle: // Google
      formatter.setFormattingStyle(astyle::STYLE_GOOGLE);
      break;

    case aspsPico: // Pico
      formatter.setFormattingStyle(astyle::STYLE_PICO);
      break;

    case aspsLisp: // Lisp
      formatter.setFormattingStyle(astyle::STYLE_LISP);
      break;

    default: // Custom
      break;
  }

  formatter.setAttachClass(cfg->ReadBool(wxT("attach_classes"), false));
  formatter.setAttachExternC(cfg->ReadBool(wxT("attach_extern_c"), true));
  formatter.setAttachNamespace(cfg->ReadBool(wxT("attach_namespaces"), true));
  formatter.setAttachInline(cfg->ReadBool(wxT("attach_inlines"), true));

  bool value = cfg->ReadBool(wxT("force_tabs"), false);
  long spaceNum = cfg->ReadLong(wxT("indentation"), 4);
  if (cfg->ReadBool(wxT("use_tabs"), false))
    formatter.setTabIndentation(spaceNum, value);
  else
    formatter.setSpaceIndentation(spaceNum);

  formatter.setCaseIndent(cfg->ReadBool(wxT("indent_case"), true));
  formatter.setClassIndent(cfg->ReadBool(wxT("indent_classes"), false));
  formatter.setLabelIndent(cfg->ReadBool(wxT("indent_labels"), false));
  formatter.setModifierIndent(cfg->ReadBool(wxT("indent_modifiers"), false));
  formatter.setNamespaceIndent(cfg->ReadBool(wxT("indent_namespaces"), true));
  formatter.setSwitchIndent(cfg->ReadBool(wxT("indent_switches"), false));
  formatter.setPreprocBlockIndent(cfg->ReadBool(wxT("indent_preproc_block"), true));
  formatter.setPreprocDefineIndent(cfg->ReadBool(wxT("indent_preproc_define"), false));
  formatter.setPreprocConditionalIndent(cfg->ReadBool(wxT("indent_preproc_cond"), false));
  formatter.setIndentCol1CommentsMode(cfg->ReadBool(wxT("indent_col1_comments"), true));
  formatter.setMinConditionalIndentOption(cfg->ReadLong(wxT("min_conditional_indent"), 2));
  formatter.setMaxInStatementIndentLength(cfg->ReadLong(wxT("max_instatement_indent"), 40));

  formatter.setBreakClosingHeaderBracketsMode(cfg->ReadBool(wxT("break_closing"), true));
  formatter.setBreakElseIfsMode(cfg->ReadBool(wxT("break_elseifs"), true));
  formatter.setAddBracketsMode(cfg->ReadBool(wxT("add_brackets"), false));
  formatter.setAddOneLineBracketsMode(cfg->ReadBool(wxT("add_one_line_brackets"), true));
  formatter.setSingleStatementsMode(!cfg->ReadBool(wxT("keep_complex"), true));
  formatter.setRemoveBracketsMode(cfg->ReadBool(wxT("remove_brackets"), false));
  formatter.setBreakOneLineBlocksMode(!cfg->ReadBool(wxT("keep_blocks"), true));
  formatter.setTabSpaceConversionMode(cfg->ReadBool(wxT("convert_tabs"), true));
  formatter.setCloseTemplatesMode(cfg->ReadBool(wxT("close_templates"), false));
  formatter.setStripCommentPrefix(cfg->ReadBool(wxT("remove_comment_prefix"), false));

  if (cfg->ReadBool(wxT("break_lines"), false))
  {
    formatter.setMaxCodeLength(wxAtoi(cfg->Read(wxT("max_line_length"), wxString(wxT("256")))));
    formatter.setBreakAfterMode(cfg->ReadBool(wxT("break_after_mode"), false));
  }
  else
    //formatter.setMaxCodeLength(INT_MAX);
    formatter.setMaxCodeLength(4096); //DEFAULT_MAX_LINELEN

  formatter.setBreakBlocksMode(cfg->ReadBool(wxT("break_blocks"), true));
  formatter.setBreakClosingHeaderBlocksMode(cfg->ReadBool(wxT("break_blocks_all"), false));
  formatter.setOperatorPaddingMode(cfg->ReadBool(wxT("pad_operators"), true));
  formatter.setParensOutsidePaddingMode(cfg->ReadBool(wxT("pad_parentheses_out"), false));
  formatter.setParensInsidePaddingMode(cfg->ReadBool(wxT("pad_parentheses_in"), true));
  formatter.setParensHeaderPaddingMode(cfg->ReadBool(wxT("pad_header"), false));
  formatter.setParensUnPaddingMode(cfg->ReadBool(wxT("unpad_parentheses"), true));
  formatter.setDeleteEmptyLinesMode(cfg->ReadBool(wxT("delete_empty_lines"), true));
  formatter.setEmptyLineFill(cfg->ReadBool(wxT("fill_empty_lines"), false));

  wxString pointerAlign = cfg->Read(wxT("pointer_align"), wxEmptyString);
  if      (pointerAlign == wxT("Type"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_TYPE);
  else if (pointerAlign == wxT("Middle"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_MIDDLE);
  else if (pointerAlign == wxT("Name"))
    formatter.setPointerAlignment(astyle::PTR_ALIGN_NAME);
  else
    formatter.setPointerAlignment(astyle::PTR_ALIGN_NONE);

  wxString referenceAlign = cfg->Read(wxT("reference_align"), wxEmptyString);
  if      (referenceAlign == wxT("Type"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_TYPE);
  else if (referenceAlign == wxT("Middle"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_MIDDLE);
  else if (referenceAlign == wxT("Name"))
    formatter.setReferenceAlignment(astyle::REF_ALIGN_NAME);
  else
    formatter.setReferenceAlignment(astyle::REF_ALIGN_NONE);
  
  cfg->SetPath(oldpath);
}
