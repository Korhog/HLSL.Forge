using System.Linq;
using Windows.UI;
using Windows.UI.Xaml.Media;

namespace HLSL.Elements
{
    using rMind.Elements;
    
    using rMind.Content.Row;
    using rMind.Nodes;

    using Base;
    using HLSL.Values;


    /// <summary>
    /// HLSL Material 
    /// </summary>
    public class Material : HeaderRowContainerBase
    {

        const string DefaultPS = @"
        struct PixelShaderInput
        {
            float3 color : COLOR0;
		};

        float4 main(PixelShaderInput input) : SV_TARGET
		{
		    return float4(input.color, 1.0f);
        };";

        const string DefaultTemplatePS = @"
        struct PixelShaderInput
        {{	
	        float4 pos : SV_POSITION;
	        float4 world : POSITION;	
	        float3 normal: NORMAL;
	        float3 color : COLOR0;
        }};

        float4 main(PixelShaderInput input) : SV_TARGET
		{{
            {0}

            float3 posLight = float3(-1.0f, 1.0f, 1.0f) - input.world.xyz;

            float4 color = {1};
            float f = dot(normalize(input.normal), normalize(posLight));
            color = float4(input.color * f, 1.0f);
            
		    return color;
        }};";

        public Material(rMindBaseController parent) : base(parent)
        {
            var row = new rMindRow
            {
                InputNode = new Node(this)
                {
                    HLSLValueBaseType = HLSLValueBaseType.FLOAT4,
                    IDS = "color",
                    Label = "Color",
                    ConnectionType = rMindNodeConnectionType.Container,
                    NodeOrientation = rMindNodeOriantation.Left,
                    Stroke = new SolidColorBrush(Colors.White)
                },
                OutputNodeType = rMindNodeConnectionType.None
            };

            AddRow(row);
        }

        public string GetPixelShader()
        {
            if (m_nodes_link.ContainsKey("color")) {
                var node = m_nodes_link["color"] as Node;
                var reverseNode = node.GetReverseNodes().FirstOrDefault() as Node;
                var value = reverseNode.GetValue();

                string color;
                if (node.HLSLValueBaseType == reverseNode.HLSLValueBaseType)
                {
                    color = value;
                }
                else
                {
                    color = HLSL.Converter.HLSLValueConverterContainer.Current().Convert(
                        new HLSLValue { HLSLValueBaseType = reverseNode.HLSLValueBaseType, HLSLValueSubType = reverseNode.HLSLValueSubType },
                        new HLSLValue { HLSLValueBaseType = node.HLSLValueBaseType },
                        value
                    );
                }
                var init = "";
                if (!string.IsNullOrEmpty(color))
                { 
                    return string.Format(DefaultTemplatePS, init, color);
                }                
            }
            return DefaultPS;
        }
    }
}
