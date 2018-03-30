using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Controls
{
    public interface ITreeSelectorItem
    {
        string Name { get; set; }

        bool Folder { get; }

        ITreeSelectorItem Parent { get; set; }

        ObservableCollection<ITreeSelectorItem> Children { get; }
    }
}
