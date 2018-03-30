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

            root.AddFolder(new TreeSelectorFolder {
                Name = "Pixel shader input",
                Parent = root
            });

            root.AddItem(new TreeSelectorItem
            {
                Name = "Color",
                SemanticName = "RGB",
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

            return root;
        }
    }
}
