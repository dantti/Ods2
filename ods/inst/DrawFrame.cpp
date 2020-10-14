#include "DrawFrame.hpp"

#include "DrawImage.hpp"
#include "SvgDesc.hpp"
#include "SvgTitle.hpp"

#include "../Length.hpp"
#include "../Ns.hpp"
#include "../ns.hxx"
#include "../Tag.hpp"

namespace ods { // ods::
namespace inst { // ods::inst::

DrawFrame::DrawFrame(Abstract *parent, Tag *tag)
: Abstract (parent, parent->ns(), id::DrawFrame)
{
	if (tag != nullptr)
		Init(tag);
}

DrawFrame::DrawFrame(const DrawFrame &cloner)
: Abstract (cloner)
{}

DrawFrame::~DrawFrame()
{
	delete svg_x_;
	delete svg_y_;
	delete svg_height_;
	delete svg_width_;
}

Abstract*
DrawFrame::Clone(Abstract *parent) const
{
	auto *p = new DrawFrame(*this);
	
	if (parent != nullptr)
		p->parent(parent);
	
	if (svg_x_ != nullptr)
		p->svg_x_ = svg_x_->Clone();
	
	if (svg_y_ != nullptr)
		p->svg_y_ = svg_y_->Clone();
	
	if (svg_height_ != nullptr)
		p->svg_height_ = svg_height_->Clone();
	
	if (svg_width_ != nullptr)
		p->svg_width_ = svg_width_->Clone();
	
	p->draw_z_index_ = draw_z_index_;
	p->draw_id_ = draw_id_;
	p->draw_name_ = draw_name_;
	p->style_rel_width_ = style_rel_width_;
	p->style_rel_height_ = style_rel_height_;
	
	return p;
}

void
DrawFrame::height(const Length *l)
{
	delete svg_height_;
	
	if (l == nullptr)
		svg_height_ = nullptr;
	else
		svg_height_ = l->Clone();
}

void
DrawFrame::Init(ods::Tag *tag)
{
	QString str;
	
	tag->Copy(ns_->svg(), ods::ns::kX, str);
	svg_x_ = Length::FromString(str);
	
	tag->Copy(ns_->svg(), ods::ns::kY, str);
	svg_y_ = Length::FromString(str);
	
	tag->Copy(ns_->svg(), ods::ns::kHeight, str);
	svg_height_ = Length::FromString(str);
	
	tag->Copy(ns_->svg(), ods::ns::kWidth, str);
	svg_width_ = Length::FromString(str);
	
	tag->Copy(ns_->draw(), ods::ns::kZIndex, draw_z_index_);
	tag->Copy(ns_->draw(), ods::ns::kId, draw_id_);
	tag->Copy(ns_->draw(), ods::ns::kName, draw_name_);
	tag->Copy(ns_->style(), ods::ns::kRelWidth, style_rel_width_);
	tag->Copy(ns_->style(), ods::ns::kRelHeight, style_rel_height_);
	
	Scan(tag);
}

inst::DrawImage*
DrawFrame::NewDrawImage()
{
	auto *p = new DrawImage(this);
	Append(p);
	return p;
}

inst::SvgDesc*
DrawFrame::NewSvgDesc()
{
	auto *p = new SvgDesc(this);
	Append(p);
	return p;
}

inst::SvgTitle*
DrawFrame::NewSvgTitle()
{
	auto *p = new SvgTitle(this);
	Append(p);
	return p;
}

void
DrawFrame::Scan(ods::Tag *scan_tag)
{
	for (auto *x: scan_tag->nodes())
	{
		if (AddText(x))
			continue;
		
		auto *tag = x->as_tag();
		
		if (tag->Is(ns_->draw(), ods::ns::kImage))
			Append(new DrawImage(this, tag));
		else if (tag->Is(ns_->svg(), ods::ns::kDesc))
			Append(new SvgDesc(this, tag));
		else if (tag->Is(ns_->svg(), ods::ns::kTitle))
			Append(new SvgTitle(this, tag));
		else
			Scan(tag);
	}
}

void
DrawFrame::SetSize(int w, int h, ods::Unit m)
{
	ods::Length len_w(w, m);
	width(&len_w);
	
	ods::Length len_h(h, m);
	height(&len_h);
}

void
DrawFrame::width(const Length *l)
{
	delete svg_width_;
	
	if (l == nullptr)
		svg_width_ = nullptr;
	else
		svg_width_ = l->Clone();
}

void
DrawFrame::x(const Length *l)
{
	delete svg_x_;
	
	if (l == nullptr)
		svg_x_ = nullptr;
	else
		svg_x_ = l->Clone();
}

void
DrawFrame::y(const Length *l)
{
	delete svg_y_;
	
	if (l == nullptr)
		svg_y_ = nullptr;
	else
		svg_y_ = l->Clone();
}

void
DrawFrame::WriteData(QXmlStreamWriter &xml)
{
	if (svg_x_ != nullptr)
		Write(xml, ns_->svg(), ods::ns::kX, svg_x_->toString());
	
	if (svg_y_ != nullptr)
		Write(xml, ns_->svg(), ods::ns::kY, svg_y_->toString());
	
	if (svg_width_ != nullptr)
		Write(xml, ns_->svg(), ods::ns::kWidth, svg_width_->toString());
	
	if (svg_height_ != nullptr)
		Write(xml, ns_->svg(), ods::ns::kHeight, svg_height_->toString());
	
	Write(xml, ns_->draw(), ods::ns::kZIndex, draw_z_index_);
	Write(xml, ns_->draw(), ods::ns::kId, draw_id_);
	Write(xml, ns_->draw(), ods::ns::kName, draw_name_);
	Write(xml, ns_->style(), ods::ns::kRelWidth, style_rel_width_);
	Write(xml, ns_->style(), ods::ns::kRelHeight, style_rel_height_);
	
	WriteNodes(xml);
}

} // ods::inst::
} // ods::
