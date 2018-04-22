#include "NumberBooleanStyle.hpp"

#include "NumberBoolean.hpp"
#include "NumberText.hpp"

#include "../Ns.hpp"
#include "../ns.hxx"
#include "../Tag.hpp"

namespace ods { // ods::
namespace inst { // ods::inst::

NumberBooleanStyle::NumberBooleanStyle(Abstract *parent, ods::Tag *tag)
 : Abstract(parent, parent->ns(), id::NumberBooleanStyle)
{
	if (tag != nullptr)
		Init(tag);
}

NumberBooleanStyle::NumberBooleanStyle(const NumberBooleanStyle &cloner)
: Abstract(cloner)
{}

NumberBooleanStyle::~NumberBooleanStyle()
{}

Abstract*
NumberBooleanStyle::Clone(Abstract *parent) const
{
	auto *p = new NumberBooleanStyle(*this);
	
	if (parent != nullptr)
		p->parent(parent);
	
	/*
	number_country_;
	number_language_;
	number_rfc_language_tag_;
	number_script_;
	number_title_;
	number_transliteration_country_;
	number_transliteration_format_;
	number_translitaration_language_;
	number_transliteration_style_;
	style_display_name_;
	style_name_;
	style_volatile_;
	*/
	
	p->number_country_ = number_country_;
	p->number_language_ = number_language_;
	p->number_rfc_language_tag_ = number_rfc_language_tag_;
	p->number_script_ = number_script_;
	p->number_title_ = number_title_;
	p->number_transliteration_country_ = number_transliteration_country_;
	p->number_transliteration_format_ = number_transliteration_format_;
	p->number_translitaration_language_ = number_translitaration_language_;
	p->number_transliteration_style_ = number_transliteration_style_;
	p->style_display_name_ = style_display_name_;
	p->style_name_ = style_name_;
	p->style_volatile_ = style_volatile_;
	
	return p;
}

void
NumberBooleanStyle::Init(ods::Tag *tag)
{
	tag->Copy(ns_->number(), ods::ns::kCountry, number_country_);
	tag->Copy(ns_->number(), ods::ns::kLanguage, number_language_);
	tag->Copy(ns_->number(), ods::ns::kRfcLanguageTag, number_rfc_language_tag_);
	tag->Copy(ns_->number(), ods::ns::kScript, number_script_);
	tag->Copy(ns_->number(), ods::ns::kTitle, number_title_);
	tag->Copy(ns_->number(), ods::ns::kTransliterationCountry, number_transliteration_country_);
	tag->Copy(ns_->number(), ods::ns::kTransliterationFormat, number_transliteration_format_);
	tag->Copy(ns_->number(), ods::ns::kTransliterationLanguage, number_translitaration_language_);
	tag->Copy(ns_->number(), ods::ns::kTransliterationStyle, number_transliteration_style_);
	tag->Copy(ns_->style(), ods::ns::kDisplayName, style_display_name_);
	tag->Copy(ns_->style(), ods::ns::kName, style_name_);
	tag->Copy(ns_->style(), ods::ns::kVolatile, style_volatile_);
	
	Scan(tag);
}

NumberBoolean*
NumberBooleanStyle::NewBoolean()
{
	auto *p = new NumberBoolean(this);
	Append(p);
	return p;
}

NumberText*
NumberBooleanStyle::NewText(const QString &s)
{
	auto *p = new NumberText(this);
	p->SetFirstString(s);
	Append(p);
	return p;
}

void
NumberBooleanStyle::Scan(ods::Tag *tag)
{
	for (auto *x: tag->nodes())
	{
		if (AddText(x))
			continue;
		
		auto *next = x->as_tag();
		
		if (next->Is(ns_->number(), ods::ns::kBoolean))
		{
			Append(new NumberBoolean(this, next));
		} else if (next->Is(ns_->number(), ods::ns::kText)) {
			Append(new NumberText(this, next));
		} else {
			Scan(next);
		}
	}
}

void
NumberBooleanStyle::WriteData(QXmlStreamWriter &xml)
{
	Write(xml, ns_->style(), ods::ns::kName, style_name_);
	WriteNodes(xml);
}

} // ods::inst::
} // ods::
