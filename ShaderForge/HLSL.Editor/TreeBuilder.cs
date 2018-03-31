using HLSL.Controls;
using HLSL.Elements;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Editor
{
    public class TreeBuilder
    {
        public static ITreeSelectorItem Build()
        {
            var root = new TreeSelectorFolder();

            var pixelInput = new TreeSelectorFolder
            {
                Name = "Pixel shader input",
                Parent = root
            };

            pixelInput.AddItem(new TreeSelectorItem
            {
                Name = "Normal",
                SemanticName = "XYZ",
                Type = typeof(PSNormal),
                Parent = root
            });

            pixelInput.AddItem(new TreeSelectorItem
            {
                Name = "Color",
                SemanticName = "RGB",
                Type = typeof(PSColor),
                Parent = root
            });

            root.AddFolder(pixelInput);

            var global = new TreeSelectorFolder
            {
                Name = "Light",
                Parent = root
            };

            global.AddItem(new TreeSelectorItem
            {
                Name = "Luminosity",
                SemanticName = "float",
                Type = typeof(Luminosity),
                Parent = root
            });

            root.AddFolder(global);            

            root.AddItem(new TreeSelectorItem
            {
                Name = "RGB",
                SemanticName = "color node",
                Type = typeof(ColorNode),
                Parent = root
            });

            root.AddItem(new TreeSelectorItem
            {
                Name = "Vector 3",
                SemanticName = "float3(0.0f, 0.0f, 0.0f)",
                Type = typeof(Vector3Node),
                Parent = root
            });

            root.AddItem(new TreeSelectorItem
            {
                Name = "multiple",
                SemanticName = "A * B",
                Type = typeof(MultipleNode),
                Parent = root
            });
            
            return root;
        }
    }
}
