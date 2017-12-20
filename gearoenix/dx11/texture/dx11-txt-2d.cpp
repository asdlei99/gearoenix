#include "dx11-txt-2d.hpp"
#ifdef USE_DIRECTX11
#include "../../render/texture/rnd-txt-png.hpp"
#include "../../system/sys-log.hpp"
#include "../dx11-engine.hpp"
#include "../../core/cr-static.hpp"
#include "../dx11-check.hpp"

gearoenix::dx11::texture::Texture2D::Texture2D(system::File* file, Engine* eng, std::shared_ptr<core::EndCaller> end):
	engine(eng)
{
    std::vector<unsigned char> img_data;
    unsigned int imgw, imgh;
    render::texture::PNG::decode(file, img_data, imgw, imgh);
	D3D11_TEXTURE2D_DESC desc;
	setz(desc);
	desc.Width = imgw;
	desc.Height = imgh;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage= D3D11_USAGE_IMMUTABLE;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
	D3D11_SHADER_RESOURCE_VIEW_DESC sdesc;
	setz(sdesc);
	sdesc.Format = desc.Format;
	sdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	sdesc.Texture2D.MipLevels = -1;
    eng->add_load_function([this, desc, sdesc, img_data, end] () -> void {
		D3D11_SUBRESOURCE_DATA subsrcdata;
		subsrcdata.pSysMem = img_data.data();
		subsrcdata.SysMemPitch = desc.Width * 4;
		ID3D11Device* dev = engine->get_device();
		ID3D11Texture2D* txt = nullptr;
		GXHRCHK(dev->CreateTexture2D(&desc, &subsrcdata, &txt));
		GXHRCHK(dev->CreateShaderResourceView(txt, &sdesc, &srv));
		engine->get_context()->GenerateMips(srv);
		txt->Release();
		(void)end;
	});
}

gearoenix::dx11::texture::Texture2D::~Texture2D()
{
	srv->Release();
}

const ID3D11ShaderResourceView* gearoenix::dx11::texture::Texture2D::get_shader_resource_view() const
{
	return srv;
}

void gearoenix::dx11::texture::Texture2D::bind(unsigned int slot) const {
	engine->get_context()->PSSetShaderResources(slot, 1, &srv);
}
#endif
